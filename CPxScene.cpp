#include <PxPhysicsAPI.h>
#include "CPxScene.h"
#include "CPxDefaultAllocator.h"

CPxPvdSceneClient CPxScene_getScenePvdClient(CPxScene cs)
{
	CPxPvdSceneClient cPvdSceneClient{};
	cPvdSceneClient.obj = static_cast<physx::PxScene*>(cs.obj)->getScenePvdClient();

	return cPvdSceneClient;
}

void CPxScene_addActor(CPxScene cs, CPxActor cActor)
{
	static_cast<physx::PxScene*>(cs.obj)->addActor(*static_cast<physx::PxActor*>(cActor.obj));
}

void CPxScene_simulate(CPxScene cs, CPxReal elapsedTime)
{
	static_cast<physx::PxScene*>(cs.obj)->simulate(elapsedTime, 0, cs.scratchBuffer, cs.scratchBufferSize, true);
}

void CPxScene_collide(CPxScene cs, CPxReal elapsedTime)
{
	static_cast<physx::PxScene*>(cs.obj)->collide(elapsedTime, 0, cs.scratchBuffer, cs.scratchBufferSize, true);
}

bool CPxScene_fetchCollision(CPxScene cs, bool block)
{
	return static_cast<physx::PxScene*>(cs.obj)->fetchCollision(block);
}

void CPxScene_advance(CPxScene cs)
{
	static_cast<physx::PxScene*>(cs.obj)->advance();
}

bool CPxScene_fetchResults(CPxScene cs, bool block, CPxU32* errorState)
{
	return static_cast<physx::PxScene*>(cs.obj)->fetchResults(block, errorState);
}

void CPxScene_setScratchBuffer(CPxScene cs, uint32_t multiplesOf16k)
{
	if (cs.scratchBuffer != NULL)
	{
		CPxDealloc(cs.scratchBuffer);
		cs.scratchBuffer = NULL;
		cs.scratchBufferSize = 0;
	}

	if (multiplesOf16k == 0)
		return;

	cs.scratchBufferSize = 1024 * 16 * multiplesOf16k;
	cs.scratchBuffer = CPxAlloc(cs.scratchBufferSize);
}

void CPxRaycastHitFromPx(CPxRaycastHit& cHit, const physx::PxRaycastHit& pHit)
{
	cHit.actor.obj = pHit.actor;
	cHit.distance = pHit.distance;
	cHit.faceIndex = pHit.faceIndex;
	cHit.flags = static_cast<CPxHitFlag>(static_cast<physx::PxU16>(pHit.flags));
	cHit.normal = NewCPxVec3(pHit.normal.x, pHit.normal.y, pHit.normal.z);
	cHit.position = NewCPxVec3(pHit.position.x, pHit.position.y, pHit.position.z);
	cHit.shape.obj = pHit.shape;
	cHit.u = pHit.u;
	cHit.v = pHit.v;
}

bool CPxScene_raycast(CPxScene cs, CPxVec3* origin, CPxVec3* unitDir, CPxReal distance, CPxRaycastBuffer** hitRet)
{
	physx::PxRaycastBuffer pBuf;
	bool ret = static_cast<physx::PxScene*>(cs.obj)->raycast(physx::PxVec3(origin->x, origin->y, origin->z), physx::PxVec3(unitDir->x, unitDir->y, unitDir->z), distance, pBuf);

	*hitRet = (CPxRaycastBuffer*)CPxAlloc(sizeof(CPxRaycastBuffer));
	CPxRaycastBuffer* hit = *hitRet;
	hit->hasBlock = pBuf.hasBlock;
	if (pBuf.hasBlock)
	{
		CPxRaycastHitFromPx(hit->block, pBuf.block);
	}

	hit->nbTouches = pBuf.nbTouches;
	hit->touches = (CPxRaycastHit*)CPxAlloc(sizeof(CPxRaycastHit) * hit->nbTouches);
	for (size_t i = 0; i < pBuf.nbTouches; i++)
	{
		CPxRaycastHitFromPx(hit->touches[i], pBuf.touches[i]);
	}

	return ret;
}

bool CPxScene_raycastWithHitBuffer(CPxScene cs, CPxVec3* origin, CPxVec3* unitDir, CPxReal distance, CPxRaycastBuffer* hit, CPxU32 touchesToRead)
{
	physx::PxRaycastBuffer pBuf;
	bool ret = static_cast<physx::PxScene*>(cs.obj)->raycast(physx::PxVec3(origin->x, origin->y, origin->z), physx::PxVec3(unitDir->x, unitDir->y, unitDir->z), distance, pBuf);

	hit->hasBlock = pBuf.hasBlock;
	if (pBuf.hasBlock)
	{
		CPxRaycastHitFromPx(hit->block, pBuf.block);
	}

	//We read a max of touchesToRead
	if (pBuf.nbTouches > touchesToRead)
	{
		hit->nbTouches = touchesToRead;
	}
	else
	{
		hit->nbTouches = pBuf.nbTouches;
	}

	for (size_t i = 0; i < hit->nbTouches; i++)
	{
		CPxRaycastHitFromPx(hit->touches[i], pBuf.touches[i]);
	}

	return ret;
}

void CPxScene_release(CPxScene cs)
{
	static_cast<physx::PxScene*>(cs.obj)->release();

	if (cs.scratchBuffer != NULL)
	{
		CPxDealloc(cs.scratchBuffer);
		cs.scratchBuffer = NULL;
	}
}

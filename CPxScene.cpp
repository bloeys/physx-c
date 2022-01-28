#include <PxPhysicsAPI.h>
#include "CPxScene.h"

CPxPvdSceneClient* CPxScene_getScenePvdClient(CPxScene* cs)
{
	CPxPvdSceneClient* cPvdSceneClient = (CPxPvdSceneClient*)malloc(sizeof(CPxPvdSceneClient));
	cPvdSceneClient->obj = static_cast<physx::PxScene*>(cs->obj)->getScenePvdClient();

	return cPvdSceneClient;
}

void CPxScene_addActor(CPxScene* cScene, CPxActor cActor)
{
	static_cast<physx::PxScene*>(cScene->obj)->
		addActor(*static_cast<physx::PxActor*>(cActor.obj));
}

void CPxScene_simulate(CPxScene* cs, CPxReal elapsedTime)
{
	static_cast<physx::PxScene*>(cs->obj)->simulate(elapsedTime, 0, cs->scratchBuffer, cs->scratchBufferSize, true);
}

bool CPxScene_fetchResults(CPxScene* cs, bool block, CPxU32* errorState)
{
	return static_cast<physx::PxScene*>(cs->obj)->fetchResults(block, errorState);
}

void CPxScene_setScratchBuffer(CPxScene* cs, uint32_t multiplesOf16k)
{
	physx::PxDefaultAllocator pa;

	if (cs->scratchBuffer != NULL)
	{
		pa.deallocate(cs->scratchBuffer);
		cs->scratchBuffer = NULL;
		cs->scratchBufferSize = 0;
	}

	if (multiplesOf16k == 0)
		return;

	cs->scratchBufferSize = 1024 * 16 * multiplesOf16k;
	cs->scratchBuffer = pa.allocate(cs->scratchBufferSize, 0, 0, 0);
}


void CPxScene_release(CPxScene* cs)
{
	static_cast<physx::PxScene*>(cs->obj)->release();

	if (cs->scratchBuffer != NULL)
	{
		physx::PxDefaultAllocator pa;
		pa.deallocate(cs->scratchBuffer);
		cs->scratchBuffer = NULL;
	}

	free(cs);
}
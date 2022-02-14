#include <PxPhysicsAPI.h>
#include "CPxSceneDesc.h"
#include "CPxDefaultAllocator.h"

class SimEventCallback : public physx::PxSimulationEventCallback {

public:

	void onConstraintBreak(physx::PxConstraintInfo* /*constraints*/, physx::PxU32 /*count*/) override { printf("onConstraintBreak\n"); }
	void onWake(physx::PxActor** /*actors*/, physx::PxU32 /*count*/) override { printf("onWake\n"); }
	void onSleep(physx::PxActor** /*actors*/, physx::PxU32 /*count*/) override { printf("onSleep\n"); }
	void onTrigger(physx::PxTriggerPair* /*pairs*/, physx::PxU32 /*count*/) override { printf("onTrigger\n"); }
	void onAdvance(const physx::PxRigidBody* const* /*bodyBuffer*/, const physx::PxTransform* /*poseBuffer*/, const physx::PxU32 /*count*/) override { printf("onAdvance\n"); }

	void onContact(const physx::PxContactPairHeader& pairHeader, const physx::PxContactPair* pairs, physx::PxU32 nbPairs) override {

		auto e = pairHeader.pairs[0].events;
		if (e & physx::PxPairFlag::eNOTIFY_TOUCH_FOUND) {
			printf("Collision enter\n");
		}
		else if (e & physx::PxPairFlag::eNOTIFY_TOUCH_PERSISTS) {
			printf("Collision persist\n");
		}
		else if (e & physx::PxPairFlag::eNOTIFY_TOUCH_LOST) {
			printf("Collision lost\n");
		}
	}
};

physx::PxFilterFlags CollisionFilterShader(
	physx::PxFilterObjectAttributes attributes0, physx::PxFilterData filterData0,
	physx::PxFilterObjectAttributes attributes1, physx::PxFilterData filterData1,
	physx::PxPairFlags& retPairFlags, const void* /*constantBlock*/, physx::PxU32 /*constantBlockSize*/)
{
	// let triggers through
	if (physx::PxFilterObjectIsTrigger(attributes0) || physx::PxFilterObjectIsTrigger(attributes1))
	{
		retPairFlags = physx::PxPairFlag::eTRIGGER_DEFAULT;
		return physx::PxFilterFlag::eDEFAULT;
	}
	// generate contacts for all that were not filtered above
	retPairFlags = physx::PxPairFlag::eCONTACT_DEFAULT;

	// trigger the contact callback for pairs (A,B) where
	// the filtermask of A contains the ID of B and vice versa.
	if ((filterData0.word0 & filterData1.word2) && (filterData1.word0 & filterData0.word2) ||
		(filterData0.word1 & filterData1.word3) && (filterData1.word1 & filterData0.word3))
		retPairFlags |= physx::PxPairFlag::eNOTIFY_TOUCH_FOUND | physx::PxPairFlag::eNOTIFY_TOUCH_PERSISTS | physx::PxPairFlag::eNOTIFY_TOUCH_LOST;

	return physx::PxFilterFlag::eDEFAULT;
}

SimEventCallback sec;
CPxSceneDesc* NewCPxSceneDesc(CPxTolerancesScale cscale)
{
	physx::PxTolerancesScale scale;
	scale.length = cscale.length;
	scale.speed = cscale.speed;

	physx::PxSceneDesc* sceneDesc = new physx::PxSceneDesc(scale);
	sceneDesc->simulationEventCallback = &sec;
	sceneDesc->filterShader = CollisionFilterShader;

	CPxSceneDesc* cpSceneDesc = (CPxSceneDesc*)CPxAlloc(sizeof(CPxSceneDesc));
	cpSceneDesc->obj = sceneDesc;

	return cpSceneDesc;
}

void CPxSceneDesc_set_gravity(CPxSceneDesc* cSceneDesc, CPxVec3 g)
{
	static_cast<physx::PxSceneDesc*>(cSceneDesc->obj)->gravity = physx::PxVec3(g.x, g.y, g.z);
}

void CPxSceneDesc_set_cpuDispatcher(CPxSceneDesc* csd, CPxCpuDispatcher* cDefDispatcher)
{
	static_cast<physx::PxSceneDesc*>(csd->obj)->cpuDispatcher = static_cast<physx::PxCpuDispatcher*>(cDefDispatcher->obj);
}

void FreeCPxSceneDesc(CPxSceneDesc* cSceneDesc)
{
	delete static_cast<physx::PxSceneDesc*>(cSceneDesc->obj);
	CPxDealloc(cSceneDesc);
}

#include <PxPhysicsAPI.h>
#include "CPxPhysics.h"

CPxPhysics* CPxCreatePhysics(CPxFoundation* cfoundation, CPxTolerancesScale cscale, bool trackOutstandingAllocations, CPxPvd* cpvd)
{
	physx::PxTolerancesScale tolerances;
	tolerances.length = cscale.length;
	tolerances.speed = cscale.speed;

	CPxPhysics* cpPhysics = (CPxPhysics*)malloc(sizeof(CPxPhysics));
	cpPhysics->obj = PxCreatePhysics(PX_PHYSICS_VERSION, *static_cast<physx::PxFoundation*>(cfoundation->obj), tolerances, trackOutstandingAllocations, static_cast<physx::PxPvd*>(cpvd->obj));

	return cpPhysics;
}

CPxScene* CPxPhysics_createScene(CPxPhysics* cp, CPxSceneDesc* csd)
{
	CPxScene* cs = (CPxScene*)malloc(sizeof(CPxScene));
	cs->scratchBuffer = NULL;
	cs->scratchBufferSize = 0;
	cs->obj = static_cast<physx::PxPhysics*>(cp->obj)->createScene(*static_cast<physx::PxSceneDesc*>(csd->obj));

	return cs;
}

CPxMaterial* CPxPhysics_createMaterial(CPxPhysics* cp, CPxReal staticFriction, CPxReal dynamicFriction, CPxReal restitution)
{
	CPxMaterial* cm = (CPxMaterial*)malloc(sizeof(CPxMaterial));
	cm->obj = static_cast<physx::PxPhysics*>(cp->obj)->createMaterial(staticFriction, dynamicFriction, restitution);

	return cm;
}


void CPxPhysics_release(CPxPhysics* cpp)
{
	static_cast<physx::PxPhysics*>(cpp->obj)->release();
	free(cpp);
}

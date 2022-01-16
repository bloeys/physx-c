#include <PxPhysicsAPI.h>
#include "CPxPhysics.h"

CPxPhysics* CPxCreatePhysics(CPxU32 version, CPxFoundation* cfoundation, const CPxTolerancesScale& cscale, bool trackOutstandingAllocations, CPxPvd* cpvd)
{
	physx::PxTolerancesScale tolerances;
	tolerances.length = cscale.length;
	tolerances.speed = cscale.speed;

	CPxPhysics* cpPhysics = (CPxPhysics*)malloc(sizeof(CPxPhysics));
	cpPhysics->obj = PxCreatePhysics(version, *static_cast<physx::PxFoundation*>(cfoundation->obj), tolerances, trackOutstandingAllocations, static_cast<physx::PxPvd*>(cpvd->obj));

	return cpPhysics;
}

CPxScene* CPxPhysics_createScene(CPxPhysics* cp, CPxSceneDesc* csd)
{
	CPxScene* cs = (CPxScene*)malloc(sizeof(CPxScene));
	cs->obj = static_cast<physx::PxPhysics*>(cp->obj)->createScene(*static_cast<physx::PxSceneDesc*>(csd->obj));

	return cs;
}


void CPxPhysics_release(CPxPhysics* cpp)
{
	static_cast<physx::PxPhysics*>(cpp->obj)->release();
	free(cpp);
}

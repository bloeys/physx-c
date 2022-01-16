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
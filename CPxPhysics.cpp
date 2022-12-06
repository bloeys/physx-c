#include <PxPhysicsAPI.h>
#include "CPxPhysics.h"
#include "CPxTransformHelpers.h"
#include "CPxDefaultAllocator.h"

CPxPhysics* CPxCreatePhysics(CPxFoundation* cfoundation, CPxTolerancesScale cscale, bool trackOutstandingAllocations, CPxPvd* cpvd)
{
	physx::PxTolerancesScale tolerances;
	tolerances.length = cscale.length;
	tolerances.speed = cscale.speed;

	CPxPhysics* cpPhysics = (CPxPhysics*)CPxAlloc(sizeof(CPxPhysics));
	if (cpvd != NULL) {
		cpPhysics->obj = PxCreatePhysics(PX_PHYSICS_VERSION, *static_cast<physx::PxFoundation*>(cfoundation->obj), tolerances, trackOutstandingAllocations, static_cast<physx::PxPvd*>(cpvd->obj));
	}
	else {
		cpPhysics->obj = PxCreatePhysics(PX_PHYSICS_VERSION, *static_cast<physx::PxFoundation*>(cfoundation->obj), tolerances, trackOutstandingAllocations);
	}

	return cpPhysics;
}

CPxScene* CPxPhysics_createScene(CPxPhysics* cp, CPxSceneDesc* csd)
{
	CPxScene* cs = (CPxScene*)CPxAlloc(sizeof(CPxScene));
	cs->scratchBuffer = NULL;
	cs->scratchBufferSize = 0;
	cs->obj = static_cast<physx::PxPhysics*>(cp->obj)->createScene(*static_cast<physx::PxSceneDesc*>(csd->obj));

	return cs;
}

CPxMaterial* CPxPhysics_createMaterial(CPxPhysics* cp, CPxReal staticFriction, CPxReal dynamicFriction, CPxReal restitution)
{
	CPxMaterial* cm = (CPxMaterial*)CPxAlloc(sizeof(CPxMaterial));
	cm->obj = static_cast<physx::PxPhysics*>(cp->obj)->createMaterial(staticFriction, dynamicFriction, restitution);

	return cm;
}

CPxRigidDynamic* CPxPhysics_createRigidDynamic(CPxPhysics* cp, CPxTransform* ctr)
{
	CPxRigidDynamic* crd = (CPxRigidDynamic*)CPxAlloc(sizeof(CPxRigidDynamic));
	crd->obj = static_cast<physx::PxPhysics*>(cp->obj)->createRigidDynamic(CPxTransform_toPxTransform(*ctr));
	return crd;
}

CPxRigidStatic* CPxPhysics_createRigidStatic(CPxPhysics* cp, CPxTransform* ctr)
{
	CPxRigidStatic* crs = (CPxRigidStatic*)CPxAlloc(sizeof(CPxRigidStatic));
	crs->obj = static_cast<physx::PxPhysics*>(cp->obj)->createRigidStatic(CPxTransform_toPxTransform(*ctr));
	return crs;
}

void CPxPhysics_release(CPxPhysics* cpp)
{
	static_cast<physx::PxPhysics*>(cpp->obj)->release();
	CPxDealloc(cpp);
}

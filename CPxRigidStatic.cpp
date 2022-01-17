#include <PxPhysicsAPI.h>
#include "CPxRigidStatic.h"

CPxRigidStatic* CPxCreatePlane(CPxPhysics* sdk, CPxPlane* plane, CPxMaterial* material)
{
	CPxRigidStatic* crs = (CPxRigidStatic*)malloc(sizeof(CPxRigidStatic));
	crs->obj = physx::PxCreatePlane(
		*static_cast<physx::PxPhysics*>(sdk->obj),
		*static_cast<physx::PxPlane*>(plane->obj),
		*static_cast<physx::PxMaterial*>(material->obj));

	return crs;
}

CPxActor* CPxRigidStatic_toCPxActor(CPxRigidStatic* crs)
{
	CPxActor* ca = (CPxActor*)malloc(sizeof(CPxActor));
	ca->obj = static_cast<physx::PxActor*>(crs->obj);
	return ca;
}
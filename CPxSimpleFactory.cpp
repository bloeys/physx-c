#include "PxPhysicsAPI.h"
#include "CPxSimpleFactory.h"

CPxRigidStatic* CPxCreatePlane(CPxPhysics* sdk, CPxPlane* plane, CPxMaterial* material)
{
	CPxRigidStatic* crs = (CPxRigidStatic*)malloc(sizeof(CPxRigidStatic));
	crs->obj = physx::PxCreatePlane(
		*static_cast<physx::PxPhysics*>(sdk->obj),
		*static_cast<physx::PxPlane*>(plane->obj),
		*static_cast<physx::PxMaterial*>(material->obj));

	return crs;
}
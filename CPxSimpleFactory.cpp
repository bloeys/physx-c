#include "PxPhysicsAPI.h"
#include "CPxSimpleFactory.h"

CPxRigidStatic CPxCreatePlane(CPxPhysics sdk, CPxPlane* plane, CPxMaterial material)
{
	CPxRigidStatic crs{};
	crs.obj = physx::PxCreatePlane(
		*static_cast<physx::PxPhysics*>(sdk.obj),
		physx::PxPlane(plane->n.x, plane->n.y, plane->n.z, plane->d),
		*static_cast<physx::PxMaterial*>(material.obj)
	);

	return crs;
}
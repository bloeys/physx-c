#include <PxPhysicsAPI.h>
#include "CPxRigidStatic.h"

CPxActor CPxRigidStatic_toCPxActor(CPxRigidStatic crs)
{
	CPxActor ca;
	ca.obj = static_cast<physx::PxActor*>(crs.obj);
	return ca;
}

CPxRigidActor CPxRigidStatic_toCPxRigidActor(CPxRigidStatic crs)
{
	CPxRigidActor ca;
	ca.obj = static_cast<physx::PxRigidActor*>(crs.obj);
	return ca;
}

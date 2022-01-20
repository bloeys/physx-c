#include <PxPhysicsAPI.h>
#include "CPxRigidDynamic.h"

CPxActor CPxRigidDynamic_toCPxActor(CPxRigidDynamic* crd)
{
	CPxActor ca;
	ca.obj = static_cast<physx::PxActor*>(crd->obj);

	return ca;
}
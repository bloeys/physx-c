#include "CPxShape.h"
#include "PxPhysicsAPI.h"
#include "CPxTransformHelpers.h"

void CPxShape_setLocalPose(CPxShape* cs, CSTRUCT CPxTransform* tr)
{
	static_cast<physx::PxShape*>(cs->obj)->setLocalPose(CPxTransform_toPxTransform(*tr));
}

CPxTransform CPxShape_getLocalPose(CPxShape* cs)
{
	return PxTransform_toCPxTransform(static_cast<physx::PxShape*>(cs->obj)->getLocalPose());
}
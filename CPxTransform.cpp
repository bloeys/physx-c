#include "PxPhysicsAPI.h"
#include "CPxTransform.h"

physx::PxTransform CPxTransform_toPxTransform(const CPxTransform& ctr)
{
	return physx::PxTransform(ctr.p.x, ctr.p.y, ctr.p.z, physx::PxQuat(ctr.q.x, ctr.q.y, ctr.q.z, ctr.q.w));
}
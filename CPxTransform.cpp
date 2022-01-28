#include "PxPhysicsAPI.h"
#include "CPxTransform.h"

CPxTransform NewCPxTransform(CPxVec3* v, CPxQuat* q)
{
	CPxTransform t;
	t.p = *v;
	t.q = *q;

	return t;
}

physx::PxTransform CPxTransform_toPxTransform(const CPxTransform& ctr)
{
	return physx::PxTransform(ctr.p.x, ctr.p.y, ctr.p.z, physx::PxQuat(ctr.q.x, ctr.q.y, ctr.q.z, ctr.q.w));
}

CPxTransform PxTransform_toCPxTransform(const physx::PxTransform& tr)
{
	CPxVec3 cv = NewCPxVec3(tr.p.x, tr.p.y, tr.p.z);
	CPxQuat cq = NewCPxQuatXYZW(tr.q.x, tr.q.y, tr.q.z, tr.q.w);
	return NewCPxTransform(&cv, &cq);
}

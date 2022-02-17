#ifndef CPxTransformHelpers_H
#define CPxTransformHelpers_H

#include "CPxTransform.h"

//unexported helpers
namespace physx
{
	class PxTransform;
}

CPxInternalAPI physx::PxTransform CPxTransform_toPxTransform(const CPxTransform&);
CPxInternalAPI CPxInline CSTRUCT CPxTransform PxTransform_toCPxTransform(const physx::PxTransform& tr)
{
	CSTRUCT CPxVec3 cv = NewCPxVec3(tr.p.x, tr.p.y, tr.p.z);
	CSTRUCT CPxQuat cq = NewCPxQuatXYZW(tr.q.x, tr.q.y, tr.q.z, tr.q.w);
	return NewCPxTransform(&cv, &cq);
}

#endif // !CPxTransformHelpers_H
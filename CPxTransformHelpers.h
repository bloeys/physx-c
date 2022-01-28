#ifndef CPxTransformHelpers_H
#define CPxTransformHelpers_H

#include "CPxTransform.h"

//unexported helpers
namespace physx
{
	class PxTransform;
}

CPxInternalAPI CPxInline physx::PxTransform CPxTransform_toPxTransform(const CPxTransform&);
CPxInternalAPI CPxInline CPxTransform PxTransform_toCPxTransform(const physx::PxTransform&);

#endif // !CPxTransformHelpers_H
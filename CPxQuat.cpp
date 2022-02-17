#include "CPxQuat.h"
#include <PxPhysicsAPI.h>

CPxQuat NewCPxQuat(float angleRads, float x, float y, float z)
{
	const float a = angleRads * 0.5f;
	const float s = physx::PxSin(a);

	CPxQuat q;
	q.w = physx::PxCos(a);
	q.x = x * s;
	q.y = y * s;
	q.z = z * s;

	return q;
}
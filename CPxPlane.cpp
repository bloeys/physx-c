#include <PxPhysicsAPI.h>
#include "CPxPlane.h"
#include "CPxDefaultAllocator.h"

CPxPlane* NewCPxPlane(float nx, float ny, float nz, float distance)
{
	CPxPlane* cp = (CPxPlane*)CPxAlloc(sizeof(CPxPlane));
	cp->obj = new physx::PxPlane(nx, ny, nz, distance);
	return cp;
}

void CPxPlane_release(CPxPlane* cp)
{
	delete static_cast<physx::PxPlane*>(cp->obj);
	CPxDealloc(cp);
}

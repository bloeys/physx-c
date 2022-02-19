#include "CPxRaycastBuffer.h"
#include "CPxDefaultAllocator.h"

CPxRaycastBuffer* NewCPxRaycastBufferWithAlloc(CPxU32 maxTouches)
{
	CPxRaycastBuffer* rb = (CPxRaycastBuffer*)CPxAlloc(sizeof(CPxRaycastBuffer));
	rb->touches = (CPxRaycastHit*)CPxAlloc(sizeof(CPxRaycastHit) * maxTouches);
	return rb;
}

void CPxRaycastBuffer_release(CPxRaycastBuffer* crb)
{
	CPxDealloc(crb->touches);
	CPxDealloc(crb);
}
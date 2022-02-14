#include <PxPhysicsAPI.h>
#include "CPxPvdTransport.h"
#include "CPxDefaultAllocator.h"

CPxPvdTransport* CPxDefaultPvdSocketTransportCreate(const char* host, int port, int timeoutInMillis)
{
	CPxPvdTransport* cpPvdTr = (CPxPvdTransport*)CPxAlloc(sizeof(*cpPvdTr));
	cpPvdTr->obj = physx::PxDefaultPvdSocketTransportCreate(host, port, timeoutInMillis);

	return cpPvdTr;
}

void CPxPvdTransport_release(CPxPvdTransport* cppt)
{
	static_cast<physx::PxPvdTransport*>(cppt->obj)->release();
	CPxDealloc(cppt);
}
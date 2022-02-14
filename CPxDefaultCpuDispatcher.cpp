#include<PxPhysicsAPI.h>
#include "CPxDefaultCpuDispatcher.h"
#include "CPxDefaultAllocator.h"

CPxDefaultCpuDispatcher* CPxDefaultCpuDispatcherCreate(CPxU32 numThreads, CPxU32 affinityMasks)
{
	CPxDefaultCpuDispatcher* cdcd = (CPxDefaultCpuDispatcher*)CPxAlloc(sizeof(CPxDefaultCpuDispatcher));
	cdcd->obj = physx::PxDefaultCpuDispatcherCreate(numThreads, &affinityMasks);
	return cdcd;
}

CPxCpuDispatcher* CPxDefaultCpuDispatcher_toCPxCpuDispatcher(CPxDefaultCpuDispatcher* cdcd)
{
	CPxCpuDispatcher* cCpuDisp = (CPxCpuDispatcher*)CPxAlloc(sizeof(CPxCpuDispatcher));
	cCpuDisp->obj = cdcd->obj;
	return cCpuDisp;
}

void CPxDefaultCpuDispatcher_release(CPxDefaultCpuDispatcher* cdcd)
{
	static_cast<physx::PxDefaultCpuDispatcher*>(cdcd->obj)->release();
	CPxDealloc(cdcd);
}
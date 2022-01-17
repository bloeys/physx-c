#include<PxPhysicsAPI.h>
#include "CPxDefaultCpuDispatcher.h"

CPxDefaultCpuDispatcher* CPxDefaultCpuDispatcherCreate(CPxU32 numThreads, CPxU32 affinityMasks)
{
	CPxDefaultCpuDispatcher* cdcd = (CPxDefaultCpuDispatcher*)malloc(sizeof(CPxDefaultCpuDispatcher));
	cdcd->obj = physx::PxDefaultCpuDispatcherCreate(numThreads, &affinityMasks);
	return cdcd;
}

CPxCpuDispatcher* CPxDefaultCpuDispatcher_toCPxCpuDispatcher(CPxDefaultCpuDispatcher* cdcd)
{
	CPxCpuDispatcher* cCpuDisp = (CPxCpuDispatcher*)malloc(sizeof(CPxCpuDispatcher));
	cCpuDisp->obj = cdcd->obj;
	return cCpuDisp;
}


void CPxDefaultCpuDispatcher_release(CPxDefaultCpuDispatcher* cdcd)
{
	static_cast<physx::PxDefaultCpuDispatcher*>(cdcd->obj)->release();
	free(cdcd);
}
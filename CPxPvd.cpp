#include <PxPhysicsAPI.h>
#include "CPxPvd.h"

CPxPvd* CPxCreatePvd(CPxFoundation* cpFoundation)
{
	physx::PxFoundation* f = static_cast<physx::PxFoundation*>(cpFoundation->obj);

	CPxPvd* cpPvd = (CPxPvd*)malloc(sizeof(*cpPvd));
	cpPvd->obj = physx::PxCreatePvd(*f);

	return cpPvd;
}

void CPxPvd_release(CPxPvd* cpp)
{
	static_cast<physx::PxPvd*>(cpp->obj)->release();
	free(cpp);
}
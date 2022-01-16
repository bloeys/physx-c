#include <PxPhysicsAPI.h>
#include "CPxPvd.h"

CPxPvd* CPxCreatePvd(CPxFoundation* cpFoundation)
{
	physx::PxFoundation* f = static_cast<physx::PxFoundation*>(cpFoundation->obj);

	CPxPvd* cpPvd = (CPxPvd*)malloc(sizeof(*cpPvd));
	cpPvd->obj = physx::PxCreatePvd(*f);

	return cpPvd;
}

bool CPxPvd_connect(CSTRUCT CPxPvd* cpPvd, CPxPvdTransport* cpPvdTr, CPxPvdInstrumentationFlag cppif)
{
	physx::PxPvd* pvd = static_cast<physx::PxPvd*>(cpPvd->obj);
	physx::PxPvdTransport* pvdTr = static_cast<physx::PxPvdTransport*>(cpPvdTr->obj);
	return pvd->connect(*pvdTr, static_cast<physx::PxPvdInstrumentationFlag::Enum>(cppif));
}


void CPxPvd_release(CPxPvd* cpp)
{
	static_cast<physx::PxPvd*>(cpp->obj)->release();
	free(cpp);
}
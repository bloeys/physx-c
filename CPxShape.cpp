#include "CPxShape.h"
#include "PxPhysicsAPI.h"
#include "CPxTransformHelpers.h"

void CPxShape_setLocalPose(CPxShape* cs, CSTRUCT CPxTransform* tr)
{
	static_cast<physx::PxShape*>(cs->obj)->setLocalPose(CPxTransform_toPxTransform(*tr));
}

CPxTransform CPxShape_getLocalPose(CPxShape* cs)
{
	return PxTransform_toCPxTransform(static_cast<physx::PxShape*>(cs->obj)->getLocalPose());
}

CPxFilterData CPxShape_getSimulationFilterData(CPxShape* cs)
{
	auto physxFilterData = static_cast<physx::PxShape*>(cs->obj)->getSimulationFilterData();

	CPxFilterData cfd;
	cfd.word0 = physxFilterData.word0;
	cfd.word1 = physxFilterData.word1;
	cfd.word2 = physxFilterData.word2;
	cfd.word3 = physxFilterData.word3;
	return cfd;
}

void CPxShape_setSimulationFilterData(CPxShape* cs, CPxFilterData* cfd)
{
	static_cast<physx::PxShape*>(cs->obj)->setSimulationFilterData(physx::PxFilterData(cfd->word0, cfd->word1, cfd->word2, cfd->word3));
}
#include <PxPhysicsAPI.h>
#include "CPxSceneDesc.h"

CPxSceneDesc* NewCPxSceneDesc(CPxTolerancesScale cscale)
{
	physx::PxTolerancesScale scale;
	scale.length = cscale.length;
	scale.speed = cscale.speed;

	physx::PxSceneDesc* sceneDesc = new physx::PxSceneDesc(scale);
	sceneDesc->filterShader = physx::PxDefaultSimulationFilterShader;

	CPxSceneDesc* cpSceneDesc = (CPxSceneDesc*)malloc(sizeof(CPxSceneDesc));
	cpSceneDesc->obj = sceneDesc;

	return cpSceneDesc;
}

void CPxSceneDesc_set_gravity(CPxSceneDesc* cSceneDesc, CPxVec3 g)
{
	static_cast<physx::PxSceneDesc*>(cSceneDesc->obj)->gravity = physx::PxVec3(g.x, g.y, g.z);
}

void CPxSceneDesc_set_cpuDispatcher(CPxSceneDesc* csd, CPxCpuDispatcher* cDefDispatcher)
{
	static_cast<physx::PxSceneDesc*>(csd->obj)->cpuDispatcher = static_cast<physx::PxCpuDispatcher*>(cDefDispatcher->obj);
}


void FreeCPxSceneDesc(CPxSceneDesc* cSceneDesc)
{
	delete static_cast<physx::PxSceneDesc*>(cSceneDesc->obj);
	free(cSceneDesc);
}

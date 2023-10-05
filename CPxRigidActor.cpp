#include <PxPhysicsAPI.h>
#include "CPxRigidActor.h"
#include "CPxDefaultAllocator.h"

void CPxRigidActor_setSimFilterData(CPxRigidActor cra, CPxFilterData cfd)
{
	physx::PxRigidActor* actor = static_cast<physx::PxRigidActor*>(cra.obj);

	const physx::PxU32 numShapes = actor->getNbShapes();
	physx::PxShape** shapes = (physx::PxShape**)CPxAlloc(sizeof(physx::PxShape*) * numShapes);
	actor->getShapes(shapes, numShapes);

	physx::PxFilterData filterData(cfd.word0, cfd.word1, cfd.word2, cfd.word3);
	for (physx::PxU32 i = 0; i < numShapes; i++)
	{
		shapes[i]->setSimulationFilterData(filterData);
	}
	CPxDealloc(shapes);
}

void CPxRigidActor_set_userData(CSTRUCT CPxRigidActor cra, void* userData)
{
	physx::PxRigidActor* actor = static_cast<physx::PxRigidActor*>(cra.obj);
	actor->userData = userData;
}

void* CPxRigidActor_get_userData(CSTRUCT CPxRigidActor cra)
{
	physx::PxRigidActor* actor = static_cast<physx::PxRigidActor*>(cra.obj);
	return actor->userData;
}
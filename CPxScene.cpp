#include <PxPhysicsAPI.h>
#include "CPxScene.h"

CPxPvdSceneClient* CPxScene_getScenePvdClient(CPxScene* cs)
{
	CPxPvdSceneClient* cPvdSceneClient = (CPxPvdSceneClient*)malloc(sizeof(CPxPvdSceneClient));
	cPvdSceneClient->obj = static_cast<physx::PxScene*>(cs->obj)->getScenePvdClient();

	return cPvdSceneClient;
}

void CPxScene_addActor(CPxScene* cScene, CPxActor* cActor)
{
	static_cast<physx::PxScene*>(cScene->obj)->
		addActor(*static_cast<physx::PxActor*>(cActor->obj));
}

void CPxScene_release(CPxScene* cs)
{
	static_cast<physx::PxScene*>(cs->obj)->release();
	free(cs);
}
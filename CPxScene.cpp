#include <PxPhysicsAPI.h>
#include "CPxScene.h"

CPxPvdSceneClient* CPxScene_getScenePvdClient(CPxScene* cs)
{
	CPxPvdSceneClient* cPvdSceneClient = (CPxPvdSceneClient*)malloc(sizeof(CPxPvdSceneClient));
	cPvdSceneClient->obj = static_cast<physx::PxScene*>(cs->obj)->getScenePvdClient();

	return cPvdSceneClient;
}

void CPxScene_release(CPxScene* cs)
{
	static_cast<physx::PxScene*>(cs->obj)->release();
	free(cs);
}
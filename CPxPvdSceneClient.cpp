#include <PxPhysicsAPI.h>
#include <cstdlib>
#include "CPxPvdSceneClient.h"
#include "CPxDefaultAllocator.h"

void CPxPvdSceneClient_setScenePvdFlag(CPxPvdSceneClient* c, CPxPvdSceneFlag flag, bool value)
{
	static_cast<physx::PxPvdSceneClient*>(c->obj)->setScenePvdFlag(static_cast<physx::PxPvdSceneFlag::Enum>(flag), value);
}

void CPxPvdSceneClient_release(CPxPvdSceneClient* c)
{
	CPxDealloc(c);
}

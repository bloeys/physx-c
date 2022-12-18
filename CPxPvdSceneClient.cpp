#include <PxPhysicsAPI.h>
#include "CPxPvdSceneClient.h"

void CPxPvdSceneClient_setScenePvdFlag(CPxPvdSceneClient c, CPxPvdSceneFlag flag, bool value)
{
	static_cast<physx::PxPvdSceneClient*>(c.obj)->setScenePvdFlag(static_cast<physx::PxPvdSceneFlag::Enum>(flag), value);
}

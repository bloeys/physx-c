#include <PxPhysicsAPI.h>
#include "CPxScene.h"

void CPxScene_release(CPxScene* cs)
{
	static_cast<physx::PxScene*>(cs->obj)->release();
	free(cs);
}
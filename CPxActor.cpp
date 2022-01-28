#include <cstdlib>
#include "CPxActor.h"
#include "PxPhysicsAPI.h"

void CPxActor_release(CPxActor* ca)
{
	static_cast<physx::PxActor*>(ca->obj)->release();
}

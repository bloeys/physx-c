#include <PxPhysicsAPI.h>
#include "CPxMaterial.h"
#include "CPxDefaultAllocator.h"

void CPxMaterial_release(CPxMaterial* cm)
{
	CPxDealloc(cm);
}

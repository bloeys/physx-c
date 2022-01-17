#include <PxPhysicsAPI.h>
#include "CPxMaterial.h"

void CPxMaterial_release(CPxMaterial* cm)
{
	free(cm);
}

#include <PxPhysicsAPI.h>
#include "CPxFoundation.h"

class SimpleErrorCallback : public physx::PxErrorCallback
{
public:
	void reportError(physx::PxErrorCode::Enum code, const char* msg, const char* file, int line)
	{
		printf("Error reported by PhysX in file '%s' at line '%d'. Code: %d; Msg: %s;\n", file, line, code, msg);
	}
};

CPxFoundation* NewCPxFoundation()
{
	CPxFoundation* cpf = new CPxFoundation;

	physx::PxDefaultAllocator allocCallback;
	SimpleErrorCallback allocErrCallback;

	cpf->obj = PxCreateFoundation(PX_PHYSICS_VERSION, allocCallback, allocErrCallback);

	return cpf;
}

void FreeCPxFoundation(CPxFoundation* cpf)
{
	delete(cpf);
}

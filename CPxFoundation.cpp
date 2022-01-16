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

CPxFoundation* CPxCreateFoundation()
{
	CPxFoundation* cpf = (CPxFoundation*)malloc(sizeof(*cpf));

	static physx::PxDefaultAllocator allocCallback;
	static SimpleErrorCallback allocErrCallback;

	cpf->obj = PxCreateFoundation(PX_PHYSICS_VERSION, allocCallback, allocErrCallback);

	return cpf;
}

void CPxFoundation_release(CPxFoundation* cpf)
{
	static_cast<physx::PxFoundation*>(cpf->obj)->release();
	free(cpf);
}

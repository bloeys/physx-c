#include <PxPhysicsAPI.h>
#include "CPxFoundation.h"
#include "CPxDefaultAllocator.h"

class SimpleErrorCallback : public physx::PxErrorCallback
{
public:
	void reportError(physx::PxErrorCode::Enum code, const char* msg, const char* file, int line)
	{
		printf("Error reported by PhysX in file '%s' at line '%d'. Code: %d; Msg: %s;\n", file, line, code, msg);
	}
};

CPxFoundation CPxCreateFoundation()
{
	CPxFoundation cpf{};

	static SimpleErrorCallback allocErrCallback;

	cpf.obj = PxCreateFoundation(PX_PHYSICS_VERSION, physxDefaultAlloc, allocErrCallback);

	return cpf;
}

void CPxFoundation_release(CPxFoundation cpf)
{
	static_cast<physx::PxFoundation*>(cpf.obj)->release();
}

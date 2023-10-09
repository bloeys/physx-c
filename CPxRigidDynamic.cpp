#include <PxPhysicsAPI.h>
#include "CPxRigidDynamic.h"
#include "CPxTransformHelpers.h"

CPxActor CPxRigidDynamic_toCPxActor(CPxRigidDynamic crd)
{
	CPxActor ca;
	ca.obj = static_cast<physx::PxActor*>(crd.obj);
	return ca;
}

CPxRigidActor CPxRigidDynamic_toCPxRigidActor(CPxRigidDynamic crd)
{
	CPxRigidActor ca;
	ca.obj = static_cast<physx::PxRigidActor*>(crd.obj);
	return ca;
}

void CPxRigidDynamic_addForce(CPxRigidDynamic crd, CPxVec3* force, CPxForceMode fmode, bool autoAwake)
{
	static_cast<physx::PxRigidDynamic*>(crd.obj)->addForce(physx::PxVec3(force->x, force->y, force->z), static_cast<physx::PxForceMode::Enum>(fmode), autoAwake);
}

void CPxRigidDynamic_addTorque(CPxRigidDynamic crd, CPxVec3* torque, CPxForceMode fmode, bool autoAwake)
{
	static_cast<physx::PxRigidDynamic*>(crd.obj)->addTorque(physx::PxVec3(torque->x, torque->y, torque->z), static_cast<physx::PxForceMode::Enum>(fmode), autoAwake);
}

CPxVec3 CPxRigidDynamic_getLinearVelocity(CPxRigidDynamic crd)
{
	physx::PxVec3 v = static_cast<physx::PxRigidDynamic*>(crd.obj)->getLinearVelocity();
	return NewCPxVec3(v.x, v.y, v.z);
}

void CPxRigidDynamic_setLinearVelocity(CPxRigidDynamic crd, CPxVec3 *velocity, bool autoAwake)
{
	static_cast<physx::PxRigidDynamic*>(crd.obj)->setLinearVelocity(physx::PxVec3(velocity->x, velocity->y, velocity->z), autoAwake);
}

CPxVec3 CPxRigidDynamic_getAngularVelocity(CPxRigidDynamic crd)
{
	physx::PxVec3 v = static_cast<physx::PxRigidDynamic*>(crd.obj)->getAngularVelocity();
	return NewCPxVec3(v.x, v.y, v.z);
}

void CPxRigidDynamic_setAngularVelocity(CPxRigidDynamic crd, CPxVec3 *velocity, bool autoAwake)
{
	static_cast<physx::PxRigidDynamic*>(crd.obj)->setAngularVelocity(physx::PxVec3(velocity->x, velocity->y, velocity->z), autoAwake);
}

CPxReal CPxRigidDynamic_getMaxLinearVelocity(CPxRigidDynamic crd)
{
	return  static_cast<physx::PxRigidDynamic*>(crd.obj)->getMaxLinearVelocity();
}

void CPxRigidDynamic_setMaxLinearVelocity(CPxRigidDynamic crd, CPxReal maxLinearVelocity)
{
	static_cast<physx::PxRigidDynamic*>(crd.obj)->setMaxLinearVelocity(maxLinearVelocity);
}

CPxReal CPxRigidDynamic_getMaxAngularVelocity(CPxRigidDynamic crd)
{
	return static_cast<physx::PxRigidDynamic*>(crd.obj)->getMaxAngularVelocity();
}

void CPxRigidDynamic_setMaxAngularVelocity(CPxRigidDynamic crd, CPxReal maxAngularVelocity)
{
	static_cast<physx::PxRigidDynamic*>(crd.obj)->setMaxAngularVelocity(maxAngularVelocity);
}

void CPxRigidDynamic_setLinearDamping(CPxRigidDynamic crd, CPxReal damping)
{
	static_cast<physx::PxRigidDynamic*>(crd.obj)->setLinearDamping(damping);
}

void CPxRigidDynamic_setAngularDamping(CPxRigidDynamic crd, CPxReal damping)
{
	static_cast<physx::PxRigidDynamic*>(crd.obj)->setAngularDamping(damping);
}

CPxReal CPxRigidDynamic_getLinearDamping(CPxRigidDynamic crd)
{
	return static_cast<physx::PxRigidDynamic*>(crd.obj)->getLinearDamping();
}

CPxReal CPxRigidDynamic_getAngularDamping(CPxRigidDynamic crd)
{
	return static_cast<physx::PxRigidDynamic*>(crd.obj)->getAngularDamping();
}

void CPxRigidDynamic_setMass(CPxRigidDynamic crd, CPxReal mass)
{
	static_cast<physx::PxRigidDynamic*>(crd.obj)->setMass(mass);
}

CPxReal CPxRigidDynamic_getMass(CPxRigidDynamic crd)
{
	return static_cast<physx::PxRigidDynamic*>(crd.obj)->getMass();
}

void CPxRigidDynamic_setRigidBodyFlag(CPxRigidDynamic crd, CPxRigidBodyFlag flag, bool value)
{
	static_cast<physx::PxRigidDynamic*>(crd.obj)->setRigidBodyFlag(static_cast<physx::PxRigidBodyFlag::Enum>(flag), value);
}

void CPxRigidDynamic_setRigidBodyFlags(CPxRigidDynamic crd, CPxRigidBodyFlag flags)
{
	static_cast<physx::PxRigidDynamic*>(crd.obj)->setRigidBodyFlags(static_cast<physx::PxRigidBodyFlag::Enum>(flags));
}

CPxRigidBodyFlag CPxRigidDynamic_getRigidBodyFlags(CPxRigidDynamic crd)
{
	uint32_t x = static_cast<physx::PxRigidDynamic*>(crd.obj)->getRigidBodyFlags();
	return static_cast<CPxRigidBodyFlag>(x);
}

void CPxRigidDynamic_setRigidDynamicLockFlag(CPxRigidDynamic crd, CPxRigidDynamicLockFlag flag, bool value)
{
	static_cast<physx::PxRigidDynamic*>(crd.obj)->setRigidDynamicLockFlag(static_cast<physx::PxRigidDynamicLockFlag::Enum>(flag), value);
}

void CPxRigidDynamic_setRigidDynamicLockFlags(CPxRigidDynamic crd, CPxRigidDynamicLockFlag flags)
{
	static_cast<physx::PxRigidDynamic*>(crd.obj)->setRigidDynamicLockFlags(static_cast<physx::PxRigidDynamicLockFlag::Enum>(flags));
}

CPxRigidDynamicLockFlag CPxRigidDynamic_getRigidDynamicLockFlags(CPxRigidDynamic crd)
{
	uint32_t x = static_cast<physx::PxRigidDynamic*>(crd.obj)->getRigidDynamicLockFlags();
	return static_cast<CPxRigidDynamicLockFlag>(x);
}

void CPxRigidDynamic_putToSleep(CPxRigidDynamic crd)
{
	static_cast<physx::PxRigidDynamic*>(crd.obj)->putToSleep();
}

CPxTransform CPxRigidDynamic_getGlobalPose(CPxRigidDynamic crd)
{
	physx::PxTransform tr = static_cast<physx::PxRigidDynamic*>(crd.obj)->getGlobalPose();
	return PxTransform_toCPxTransform(tr);
}

void CPxRigidDynamic_setGlobalPose(CPxRigidDynamic crd, CPxTransform* tr, bool autoAwake)
{
	static_cast<physx::PxRigidDynamic*>(crd.obj)->setGlobalPose(CPxTransform_toPxTransform(*tr), autoAwake);
}

CPxTransform CPxRigidDynamic_getCMassLocalPose(CPxRigidDynamic crd)
{
	physx::PxTransform tr = static_cast<physx::PxRigidDynamic*>(crd.obj)->getCMassLocalPose();
	return PxTransform_toCPxTransform(tr);
}

void CPxRigidDynamic_setCMassLocalPose(CPxRigidDynamic crd, CPxTransform* tr)
{
	static_cast<physx::PxRigidDynamic*>(crd.obj)->setCMassLocalPose(CPxTransform_toPxTransform(*tr));
}

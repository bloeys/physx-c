#include <PxPhysicsAPI.h>
#include "CExtSimpleFactory.h"

physx::PxRigidDynamic* DoPxCreateDynamic(CPxPhysics& sdk, const CPxTransform& transform, const physx::PxGeometry& geometry, CPxMaterial& material, CPxReal density, const CPxTransform& shapeOffset);

CPxRigidDynamic* CPxCreateDynamic(CPxPhysics* sdk, CPxTransform* transform, CPxGeometry geometry, CPxMaterial* material, CPxReal density, CPxTransform* shapeOffset)
{
	CPxRigidDynamic* crd = (CPxRigidDynamic*)malloc(sizeof(CPxRigidDynamic));

	switch (geometry.type)
	{
	case CPxGeometryType_eSPHERE:
		crd->obj = DoPxCreateDynamic(*sdk, *transform, physx::PxSphereGeometry(static_cast<CPxSphereGeometry*>(geometry.obj)->radius), *material, density, *shapeOffset);
		break;
	case CPxGeometryType_ePLANE:
		crd->obj = DoPxCreateDynamic(*sdk, *transform, physx::PxPlaneGeometry(), *material, density, *shapeOffset);
		break;
	case CPxGeometryType_eCAPSULE:
	{
		CPxCapsuleGeometry* ccg = static_cast<CPxCapsuleGeometry*>(geometry.obj);
		crd->obj = DoPxCreateDynamic(*sdk, *transform, physx::PxCapsuleGeometry(ccg->radius, ccg->halfHeight), *material, density, *shapeOffset);
	}
	break;
	case CPxGeometryType_eBOX:
	{
		CPxBoxGeometry* cbg = static_cast<CPxBoxGeometry*>(geometry.obj);
		crd->obj = DoPxCreateDynamic(*sdk, *transform, physx::PxBoxGeometry(cbg->hx, cbg->hy, cbg->hz), *material, density, *shapeOffset);
	}
	break;
	/*case CPxGeometryType_eCONVEXMESH:
		break;
	case CPxGeometryType_eTRIANGLEMESH:
		break;
	case CPxGeometryType_eHEIGHTFIELD:
		break;*/
	}

	return crd;
}

CPxInline physx::PxRigidDynamic* DoPxCreateDynamic(CPxPhysics& sdk, const CPxTransform& transform, const physx::PxGeometry& geometry, CPxMaterial& material, CPxReal density, const CPxTransform& shapeOffset)
{
	return physx::PxCreateDynamic(*static_cast<physx::PxPhysics*>(sdk.obj),
		physx::PxTransform(transform.p.x, transform.p.y, transform.p.z, physx::PxQuat(transform.q.x, transform.q.y, transform.q.z, transform.q.w)),
		geometry,
		*static_cast<physx::PxMaterial*>(material.obj),
		physx::PxReal(density),
		physx::PxTransform(shapeOffset.p.x, shapeOffset.p.y, shapeOffset.p.z, physx::PxQuat(shapeOffset.q.x, shapeOffset.q.y, shapeOffset.q.z, shapeOffset.q.w)));
}
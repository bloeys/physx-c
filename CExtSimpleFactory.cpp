#include <PxPhysicsAPI.h>
#include "CExtSimpleFactory.h"
#include "CPxTransformHelpers.h"
#include "CPxDefaultAllocator.h"

CPxInline physx::PxRigidDynamic* DoPxCreateDynamic(CPxPhysics& sdk, const CPxTransform& transform, const physx::PxGeometry& geometry, CPxMaterial& material, CPxReal density, const CPxTransform& shapeOffset)
{
	return physx::PxCreateDynamic(*static_cast<physx::PxPhysics*>(sdk.obj),
		CPxTransform_toPxTransform(transform),
		geometry,
		*static_cast<physx::PxMaterial*>(material.obj),
		physx::PxReal(density),
		CPxTransform_toPxTransform(shapeOffset));
}

CPxRigidDynamic CPxCreateDynamic(CPxPhysics sdk, CPxTransform* transform, CPxGeometry geometry, CPxMaterial material, CPxReal density, CPxTransform* shapeOffset)
{
	CPxRigidDynamic crd = {0};

	switch (geometry.type)
	{
	case CPxGeometryType_eSPHERE:
		crd.obj = DoPxCreateDynamic(sdk, *transform, physx::PxSphereGeometry(static_cast<CPxSphereGeometry*>(geometry.obj)->radius), material, density, *shapeOffset);
		break;
	case CPxGeometryType_ePLANE:
		crd.obj = DoPxCreateDynamic(sdk, *transform, physx::PxPlaneGeometry(), material, density, *shapeOffset);
		break;
	case CPxGeometryType_eCAPSULE:
	{
		CPxCapsuleGeometry* ccg = static_cast<CPxCapsuleGeometry*>(geometry.obj);
		crd.obj = DoPxCreateDynamic(sdk, *transform, physx::PxCapsuleGeometry(ccg->radius, ccg->halfHeight), material, density, *shapeOffset);
	}
	break;
	case CPxGeometryType_eBOX:
	{
		CPxBoxGeometry* cbg = static_cast<CPxBoxGeometry*>(geometry.obj);
		crd.obj = DoPxCreateDynamic(sdk, *transform, physx::PxBoxGeometry(cbg->hx, cbg->hy, cbg->hz), material, density, *shapeOffset);
	}
	break;

	// @TODO
	/*case CPxGeometryType_eCONVEXMESH:
		break;
	case CPxGeometryType_eTRIANGLEMESH:
		break;
	case CPxGeometryType_eHEIGHTFIELD:
		break;*/
	}

	return crd;
}

#include "CPxRigidActorExt.h"
#include "PxPhysicsAPI.h"

CPxInline CPxShape DoCreateExclusiveShape(const CPxRigidActor& actor, const physx::PxGeometry& geometry, const CPxMaterial& material, const CPxShapeFlags& shapeFlags)
{
	CPxShape cShape;
	cShape.obj = physx::PxRigidActorExt::createExclusiveShape(
		*static_cast<physx::PxRigidActor*>(actor.obj),
		geometry,
		*static_cast<physx::PxMaterial*>(material.obj),
		static_cast<physx::PxShapeFlags>(shapeFlags)
	);

	return cShape;
}

CPxShape createExclusiveShape(CPxRigidActor actor, CPxGeometry geometry, CPxMaterial* material, CPxShapeFlags shapeFlags)
{

	switch (geometry.type)
	{
	case CPxGeometryType_eSPHERE:
		return DoCreateExclusiveShape(actor, physx::PxSphereGeometry(static_cast<CPxSphereGeometry*>(geometry.obj)->radius), *material, shapeFlags);
	case CPxGeometryType_ePLANE:
		return DoCreateExclusiveShape(actor, physx::PxPlaneGeometry(), *material, shapeFlags);
	case CPxGeometryType_eCAPSULE:
	{
		CPxCapsuleGeometry* ccg = static_cast<CPxCapsuleGeometry*>(geometry.obj);
		return DoCreateExclusiveShape(actor, physx::PxCapsuleGeometry(ccg->radius, ccg->halfHeight), *material, shapeFlags);
	}
	case CPxGeometryType_eBOX:
	{
		CPxBoxGeometry* cbg = static_cast<CPxBoxGeometry*>(geometry.obj);
		return DoCreateExclusiveShape(actor, physx::PxBoxGeometry(cbg->hx, cbg->hy, cbg->hz), *material, shapeFlags);
	}
	break;
	/*case CPxGeometryType_eCONVEXMESH:
		break;
	case CPxGeometryType_eTRIANGLEMESH:
		break;
	case CPxGeometryType_eHEIGHTFIELD:
		break;*/
	}

	//NOTE: This is an invalid cast and will crash physx, with an error saying something like 'unknown shape type'.
	//We do it here intentionally because the user passed an invalid shape type (or one we don't handle yet)
	return DoCreateExclusiveShape(actor, *static_cast<physx::PxGeometry*>(geometry.obj), *material, shapeFlags);
}


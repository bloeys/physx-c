#include "CPxGeometry.h"
#include "CPxBoxGeometry.h"
#include "CPxSphereGeometry.h"

//
// CPxSphereGeometry
//

CPxSphereGeometry CPxGeometry_toCPxSphereGeometry(CPxGeometry cg)
{
	return *static_cast<CPxSphereGeometry*>(cg.obj);
}

CPxGeometry CPxSphereGeometry_toCPxGeometry(CPxSphereGeometry* csg)
{
	CPxGeometry g;
	g.obj = csg;
	g.type = CPxGeometryType_eSPHERE;
	return g;
}

//
// CPxBoxGeometry
//

CPxBoxGeometry CPxGeometry_toCPxBoxGeometry(CPxGeometry cg)
{
	return *static_cast<CPxBoxGeometry*>(cg.obj);
}

CPxGeometry CPxBoxGeometry_toCPxGeometry(CPxBoxGeometry* cbg)
{
	CPxGeometry g;
	g.obj = cbg;
	g.type = CPxGeometryType_eBOX;
	return g;
}

//
// CPxCapsuleGeometry
//

CPxCapsuleGeometry CPxGeometry_toCPxCapsuleGeometry(CPxGeometry cg)
{
	return *static_cast<CPxCapsuleGeometry*>(cg.obj);
}

CPxGeometry CPxCapsuleGeometry_toCPxGeometry(CPxCapsuleGeometry* ccg)
{
	CPxGeometry g;
	g.obj = ccg;
	g.type = CPxGeometryType_eCAPSULE;
	return g;
}
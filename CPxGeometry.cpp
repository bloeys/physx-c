#include "CPxGeometry.h"
#include "CPxBoxGeometry.h"
#include "CPxSphereGeometry.h"

//
// CPxSphereGeometry
//

CPxSphereGeometry CPxGeometry_toCPxSphere(CPxGeometry cg)
{
	return *(CPxSphereGeometry*)cg.obj;
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

CPxBoxGeometry CPxGeometry_toCPxBox(CPxGeometry cg)
{
	return *(CPxBoxGeometry*)cg.obj;
}

CPxGeometry CPxBoxGeometry_toCPxGeometry(CPxBoxGeometry* cbg)
{
	CPxGeometry g;
	g.obj = cbg;
	g.type = CPxGeometryType_eBOX;

	return g;
}
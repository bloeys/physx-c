#include "CPxPlane.h"

CPxPlane NewCPxPlane(float nx, float ny, float nz, float distance)
{
	CPxPlane cp;
	cp.n.x = nx;
	cp.n.y = ny;
	cp.n.z = nz;
	cp.d = distance;

	return cp;
}

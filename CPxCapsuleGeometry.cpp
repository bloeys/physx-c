#include "CPxCapsuleGeometry.h"

CPxCapsuleGeometry NewCPxCapsuleGeometry(CPxReal radius, CPxReal halfHeight)
{
	CPxCapsuleGeometry c;
	c.radius = radius;
	c.halfHeight = halfHeight;
	return c;
}
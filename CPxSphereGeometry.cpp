#include "CPxSphereGeometry.h"

CPxSphereGeometry NewCPxSphereGeometry(CPxReal radius)
{
	CPxSphereGeometry c;
	c.radius = radius;
	return c;
}
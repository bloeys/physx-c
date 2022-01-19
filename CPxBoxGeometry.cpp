#include "CPxGeometry.h"
#include "CPxBoxGeometry.h"

CPxBoxGeometry NewCPxBoxGeometry(float hx, float hy, float hz)
{
	CPxBoxGeometry cbg;
	cbg.hx = hx;
	cbg.hy = hy;
	cbg.hz = hz;

	return cbg;
}
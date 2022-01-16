#include "CPxTolerancesScale.h"

CPxTolerancesScale NewCPxTolerancesScale(CPxReal length, CPxReal speed)
{
	CPxTolerancesScale cpts;
	cpts.length = length;
	cpts.speed = speed;
	return cpts;
}

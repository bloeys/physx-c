#include "CPxTransform.h"

CPxTransform NewCPxTransform(CPxVec3* v, CPxQuat* q)
{
	CPxTransform t;
	t.p = *v;
	t.q = *q;

	return t;
}
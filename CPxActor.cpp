#include <cstdlib>
#include "CPxActor.h"

void CPxActor_release(CPxActor* ca)
{
	free(ca);
}

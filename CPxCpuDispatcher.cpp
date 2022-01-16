#include <cstdlib>
#include "CPxCpuDispatcher.h"

void CPxCpuDispatcher_release(CPxCpuDispatcher* c)
{
	free(c);
}

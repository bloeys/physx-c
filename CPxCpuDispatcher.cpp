#include <cstdlib>
#include "CPxCpuDispatcher.h"
#include "CPxDefaultAllocator.h"

void CPxCpuDispatcher_release(CPxCpuDispatcher* c)
{
	CPxDealloc(c);
}

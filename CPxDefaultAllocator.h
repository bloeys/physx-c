#ifndef CPxDefaultAllocator_H
#define CPxDefaultAllocator_H

#include <PxPhysicsAPI.h>

static physx::PxDefaultAllocator physxDefaultAlloc;

#define CPxAlloc(size) physxDefaultAlloc.allocate(size, 0, 0, 0);
#define CPxDealloc(ptr) physxDefaultAlloc.deallocate(ptr);

#endif // !CPxDefaultAllocator_H

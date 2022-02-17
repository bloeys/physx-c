#include <PxPhysicsAPI.h>
#include "CPxSceneDesc.h"
#include "CPxDefaultAllocator.h"
#include "CPxContactPairHeader.h"

void emptyOnContactCb(void*) {};

class SimEventCallback : public physx::PxSimulationEventCallback {

private:
	//C version of PxContactPair::extractContacts that has the same c++ logic but CPx types. We do this so we don't have to copy data twice by running PxContactPair::extractContacts then copying the produced C++ structs into C
	CPxInline CPxU32 extractContacts(const physx::PxContactPair& pair, CPxContactPairPoint* userBuffer, const CPxU32 bufferSize) const
	{
		CPxU32 nbContacts = 0;

		if (pair.contactCount && bufferSize)
		{
			physx::PxContactStreamIterator iter(pair.contactPatches, pair.contactPoints, pair.getInternalFaceIndices(), pair.patchCount, pair.contactCount);

			const CPxReal* impulses = pair.contactImpulses;

			const CPxU32 flippedContacts = (pair.flags & physx::PxContactPairFlag::eINTERNAL_CONTACTS_ARE_FLIPPED);
			const CPxU32 hasImpulses = (pair.flags & physx::PxContactPairFlag::eINTERNAL_HAS_IMPULSES);

			while (iter.hasNextPatch())
			{
				iter.nextPatch();
				while (iter.hasNextContact())
				{
					iter.nextContact();
					CPxContactPairPoint& dst = userBuffer[nbContacts];
					auto cppVec3 = iter.getContactPoint();
					dst.position = NewCPxVec3(cppVec3.x, cppVec3.y, cppVec3.z);

					dst.separation = iter.getSeparation();

					cppVec3 = iter.getContactNormal();
					dst.normal = NewCPxVec3(cppVec3.x, cppVec3.y, cppVec3.z);
					if (!flippedContacts)
					{
						dst.internalFaceIndex0 = iter.getFaceIndex0();
						dst.internalFaceIndex1 = iter.getFaceIndex1();
					}
					else
					{
						dst.internalFaceIndex0 = iter.getFaceIndex1();
						dst.internalFaceIndex1 = iter.getFaceIndex0();
					}

					if (hasImpulses)
					{
						const CPxReal impulse = impulses[nbContacts];
						dst.impulse = NewCPxVec3(dst.normal.x * impulse, dst.normal.y * impulse, dst.normal.z * impulse);
					}
					else
					{
						dst.impulse = CPxVec3{ 0 };
					}

					++nbContacts;
					if (nbContacts == bufferSize)
						return nbContacts;
				}
			}
		}

		return nbContacts;
	}

public:

	int contactPairPointBufferSize = 256;
	CPxContactPairPoint* contactPairPointsBuffer = (CPxContactPairPoint*)CPxAlloc(sizeof(CPxContactPairPoint) * contactPairPointBufferSize);

	int contactPairsBufferSize = 100;
	CPxContactPair* contactPairsBuffer = (CPxContactPair*)CPxAlloc(sizeof(CPxContactPair) * contactPairsBufferSize);
	CPxonContactCallback onContactCb = emptyOnContactCb;

	void onConstraintBreak(physx::PxConstraintInfo* /*constraints*/, physx::PxU32 /*count*/) override { printf("onConstraintBreak\n"); }
	void onWake(physx::PxActor** /*actors*/, physx::PxU32 /*count*/) override { printf("onWake\n"); }
	void onSleep(physx::PxActor** /*actors*/, physx::PxU32 /*count*/) override { printf("onSleep\n"); }
	void onTrigger(physx::PxTriggerPair* /*pairs*/, physx::PxU32 /*count*/) override { printf("onTrigger\n"); }
	void onAdvance(const physx::PxRigidBody* const* /*bodyBuffer*/, const physx::PxTransform* /*poseBuffer*/, const physx::PxU32 /*count*/) override { printf("onAdvance\n"); }

	void onContact(const physx::PxContactPairHeader& pairHeader, const physx::PxContactPair* pairs, physx::PxU32 nbPairs) override
	{
		//PERF: Can we do something better than a copy?
		CPxContactPairHeader cph;
		cph.actors[0].obj = pairHeader.actors[0];
		cph.actors[1].obj = pairHeader.actors[1];

		cph.extraDataStream = (CPxU8*)pairHeader.extraDataStream;
		cph.extraDataStreamSize = pairHeader.extraDataStreamSize;

		uint32_t f = static_cast<uint32_t>(pairHeader.flags);
		cph.flags = static_cast<CPxContactPairHeaderFlag>(f);

		//Ensure pairs buffer is big enough
		cph.nbPairs = nbPairs;
		if (nbPairs > contactPairsBufferSize) {
			CPxDealloc(contactPairsBuffer);
			contactPairsBuffer = (CPxContactPair*)CPxAlloc(sizeof(CPxContactPair) * nbPairs);
			contactPairsBufferSize = nbPairs;
		}

		//PERF: Maybe use a different way so we don't loop twice?
		//Ensure contacts buffer is big enough
		int totalContactPoints = 0;
		for (int i = 0; i < nbPairs; i++)
			totalContactPoints += pairHeader.pairs[i].contactCount;

		if (totalContactPoints > contactPairPointBufferSize)
		{
			CPxDealloc(contactPairPointsBuffer);
			contactPairPointsBuffer = (CPxContactPairPoint*)CPxAlloc(sizeof(CPxContactPairPoint) * totalContactPoints);
			contactPairPointBufferSize = totalContactPoints;
		}

		int currPoint = 0;
		cph.pairs = contactPairsBuffer;
		for (int i = 0; i < nbPairs; i++)
		{
			cph.pairs[i].contactCount = pairHeader.pairs[i].contactCount;
			cph.pairs[i].contactImpulses = (CPxReal*)pairHeader.pairs[i].contactImpulses;
			cph.pairs[i].contactPatches = (CPxU8*)pairHeader.pairs[i].contactPatches;
			cph.pairs[i].contactPoints = (CPxU8*)pairHeader.pairs[i].contactPoints;
			cph.pairs[i].contactStreamSize = (CPxU16)pairHeader.pairs[i].contactStreamSize;

			//NOTE: With this implementation we avoid copying the contactPairPoints data but the callback handler MUST copy data it wishes to keep
			//for longer than the lifetime of the callback handler, as the memory it was handed might be reused/freed.
			extractContacts(pairHeader.pairs[i], &contactPairPointsBuffer[currPoint], contactPairPointBufferSize - currPoint);
			cph.pairs[i].extractedContactPoints = &contactPairPointsBuffer[currPoint];
			currPoint += cph.pairs[i].contactCount;

			f = static_cast<uint32_t>(pairHeader.pairs[i].events);
			cph.pairs[i].events = static_cast<CPxPairFlags>(f);

			f = static_cast<uint32_t>(pairHeader.pairs[i].flags);
			cph.pairs[i].flags = static_cast<CPxContactPairFlag>(f);

			cph.pairs[i].patchCount = pairHeader.pairs[i].patchCount;
			cph.pairs[i].requiredBufferSize = pairHeader.pairs[i].requiredBufferSize;

			cph.pairs[i].shapes[0].obj = pairHeader.pairs[i].shapes[0];
			cph.pairs[i].shapes[1].obj = pairHeader.pairs[i].shapes[1];
		}

		onContactCb(&cph);
	}
};

physx::PxFilterFlags CollisionFilterShader(
	physx::PxFilterObjectAttributes attributes0, physx::PxFilterData filterData0,
	physx::PxFilterObjectAttributes attributes1, physx::PxFilterData filterData1,
	physx::PxPairFlags& retPairFlags, const void* /*constantBlock*/, physx::PxU32 /*constantBlockSize*/)
{
	// let triggers through
	if (physx::PxFilterObjectIsTrigger(attributes0) || physx::PxFilterObjectIsTrigger(attributes1))
	{
		retPairFlags = physx::PxPairFlag::eTRIGGER_DEFAULT;
		return physx::PxFilterFlag::eDEFAULT;
	}

	// generate contacts for all that were not filtered above
	retPairFlags = physx::PxPairFlag::eCONTACT_DEFAULT;

	// trigger the contact callback for pairs (A,B) where
	// the filtermask of A contains the ID of B and vice versa.
	if ((filterData0.word0 & filterData1.word2) && (filterData1.word0 & filterData0.word2) ||
		(filterData0.word1 & filterData1.word3) && (filterData1.word1 & filterData0.word3))
		retPairFlags |= physx::PxPairFlag::eNOTIFY_TOUCH_FOUND | physx::PxPairFlag::eNOTIFY_TOUCH_PERSISTS | physx::PxPairFlag::eNOTIFY_TOUCH_LOST | physx::PxPairFlag::eNOTIFY_CONTACT_POINTS;

	return physx::PxFilterFlag::eDEFAULT;
}

SimEventCallback sec;
CPxSceneDesc* NewCPxSceneDesc(CPxTolerancesScale cscale)
{
	physx::PxTolerancesScale scale;
	scale.length = cscale.length;
	scale.speed = cscale.speed;

	physx::PxSceneDesc* sceneDesc = new physx::PxSceneDesc(scale);
	sceneDesc->simulationEventCallback = &sec;
	sceneDesc->filterShader = CollisionFilterShader;

	CPxSceneDesc* cpSceneDesc = (CPxSceneDesc*)CPxAlloc(sizeof(CPxSceneDesc));
	cpSceneDesc->obj = sceneDesc;

	return cpSceneDesc;
}

void CPxSceneDesc_set_gravity(CPxSceneDesc* cSceneDesc, CPxVec3 g)
{
	static_cast<physx::PxSceneDesc*>(cSceneDesc->obj)->gravity = physx::PxVec3(g.x, g.y, g.z);
}

void CPxSceneDesc_set_cpuDispatcher(CPxSceneDesc* csd, CPxCpuDispatcher* cDefDispatcher)
{
	static_cast<physx::PxSceneDesc*>(csd->obj)->cpuDispatcher = static_cast<physx::PxCpuDispatcher*>(cDefDispatcher->obj);
}

void CPxSceneDesc_set_onContactCallback(CPxSceneDesc*, CPxonContactCallback cb)
{
	sec.onContactCb = cb;
}


void FreeCPxSceneDesc(CPxSceneDesc* cSceneDesc)
{
	delete static_cast<physx::PxSceneDesc*>(cSceneDesc->obj);
	CPxDealloc(cSceneDesc);
}

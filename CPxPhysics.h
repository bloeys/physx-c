#ifndef CPxPhysics_H
#define CPxPhysics_H

#include "CPxPvd.h"
#include "CPxFoundation.h"
#include "CPxTolerancesScale.h"

#ifdef __cplusplus
extern "C" {
#endif

	struct CPxPhysics {
		void* obj;
	};

	CPxAPI CSTRUCT CPxPhysics* CPxCreatePhysics(CPxU32 version, CSTRUCT CPxFoundation* cfoundation, const CSTRUCT CPxTolerancesScale& cscale, bool trackOutstandingAllocations = false, CSTRUCT CPxPvd* cpvd = NULL);

#ifdef __cplusplus
}
#endif

#endif
#ifndef CPxScene_H
#define CPxScene_H

#include "CPxPvdSceneClient.h"

#ifdef __cplusplus
extern "C" {
#endif

	struct CPxScene
	{
		void* obj;
	};

	CPxAPI CSTRUCT CPxPvdSceneClient* CPxScene_getScenePvdClient(CSTRUCT CPxScene*);
	CPxAPI void CPxScene_release(CSTRUCT CPxScene*);

#ifdef __cplusplus
}
#endif


#endif // !CPxScene_H

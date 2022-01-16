#ifndef CPxTolerancesScale_H
#define CPxTolerancesScale_H

#ifdef __cplusplus
extern "C" {
#endif

	struct CPxTolerancesScale
	{
		CPxReal length, speed;
	};

	CPxAPI CSTRUCT CPxTolerancesScale NewCPxTolerancesScale(CPxReal length = 1.0f, CPxReal speed = 10.0f);

#ifdef __cplusplus
}
#endif

#endif
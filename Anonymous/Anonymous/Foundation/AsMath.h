#ifndef _ANONYMOUS_MATH_H_
#define _ANONYMOUS_MATH_H_

#include <math.h>
#include <float.h>
#include "AsPreprocessor.h"

static const float AsPi = float(3.141592653589793);
static const float AsHalfPi = float(1.57079632679489661923);
static const float AsTwoPi = float(6.28318530717958647692);
static const float AsInvPi = float(0.31830988618379067154);
static const float AsInvTwoPi = float(0.15915494309189533577);
static const float AsPiDivTwo = float(1.57079632679489661923);
static const float AsPiDivFour = float(0.78539816339744830962);

inline bool AsIsFinite(float a)
{
	return (0 == ((_FPCLASS_SNAN | _FPCLASS_QNAN | _FPCLASS_NINF | _FPCLASS_PINF) & _fpclass(a)));
}

inline float AsRecipSqrt(float a)
{
	return 1.0f / sqrtf(a);
}

inline float AsMax(float a, float b)
{
	return a > b ? a : b;
}

inline float AsMin(float a, float b)
{
	return a < b ? a : b;
}

inline float AsAbs(float x)
{
	return abs(x);
}

inline float AsSqrt(float x)
{
	return sqrtf(x);
}

#endif
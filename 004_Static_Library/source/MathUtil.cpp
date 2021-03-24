#include "MathUtil.h"

float MathUtil::Max( float a, float b)
{
	return (a > b) ? a : b;
}

float MathUtil::Clamp(float min, float max, float value)
{
	float clampedValue = value;
	if (clampedValue < min) clampedValue = min;
	if (clampedValue > max) clampedValue = max;
	return clampedValue;
}
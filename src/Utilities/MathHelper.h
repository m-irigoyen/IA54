#ifndef MATHHELPER_H_
#define MATHHELPER_H_

#include <math.h>
#include <iostream>

#define PI (3.141592653589793)

float degToRad(float degrees);
float radToDeg(float radians);
float computeAngle(float x, float y);	// Computes angle (in degrees) from given
											// Helper functions
float convertToRange(float value, float minValue, float maxValue, float targetMinValue, float targetMaxValue);	// Converts given value from its range to the given range

#endif
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

void convertCoordinates(float xIn, float yIn, float widthIn, float heightIn, float& xOut, float& yOut, float widthOut, float heightOut);

bool toggle(bool value);	// If value, returns false. Else, returns true

#endif
#ifndef MATHHELPER_H_
#define MATHHELPER_H_

#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>

//#define PI (3.141592653589793)

float degToRad(float degrees);
float radToDeg(float radians);

// Computes angle (in degrees) from given direction
float computeAngle(float x, float y);	

											// Helper functions
// Converts given value from its range to the given range
float convertToRange(float value, float minValue, float maxValue, float targetMinValue, float targetMaxValue);	

// Converts coordinates into another window
void convertCoordinates(float xIn, float yIn, float widthIn, float heightIn, float& xOut, float& yOut, float widthOut, float heightOut);

// If value is true, returns false. Else, returns true
bool toggle(bool& value);	

// Returns a random number between min and max inclusive
float random(float min = 0.0f, float max = 1.0f);

// returns the scale of b compared to a. So if a is 3, and b is 6, it will return 2
float getScale(float a, float b);

#endif
#include "Utilities/MathHelper.h"

double degToRad(double degrees)
{
	return (degrees * 2*PI ) / 360;
}

double radToDeg(double radians)
{
	return (radians * 360) / (2*PI);
}

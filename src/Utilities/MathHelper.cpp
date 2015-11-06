#include "Utilities/MathHelper.h"

double degToRad(double degrees)
{
	return (degrees * 2*PI ) / 360;
}

double radToDeg(double radians)
{
	return (radians * 360) / (2*PI);
}

double computeAngle(double x, double y)
{
	if (x == 0 && y >= 0)
		return 90;
	else if (x < 0 && y < 0)
		return 270;
	else if (x >= 0 && y == 0)
		return 0;
	else if (x < 0 && y == 0)
		return 180;
	else
	{
		return atan(y / x);
	}
}

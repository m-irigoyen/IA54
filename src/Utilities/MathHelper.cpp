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

// Converts given value from its range to the given range
float convertToRange(float value, float valueOffset, float valueRange, float targetOffset, float targetRange)
{
	if (value < 0 || valueOffset < 0 || valueRange <= 0 || targetOffset < 0 || targetRange <= 0
		|| value < valueOffset || value > valueRange + valueOffset)
	{
		//cout << "ERROR : Agent::convertToRange : invalid parameters" << endl;
		//cout << "    Parameters were : " << value << ", " << valueOffset << ", " << valueRange << ", " << targetOffset << ", " << targetRange << endl;

		if (value < 0)
			return -1.0f;
		if (value > valueOffset + valueRange)
			value = valueOffset + valueRange;
		else if (value < valueOffset)
			value = valueOffset;
	}

	//valueOffset		-> value				-> valueRange+valueOffset
	// 0				-> value-valueOffset	-> valueRange
	//float translatedValue = (value * valueRange) / (valueRange + valueOffset);
	float translatedValue = value - valueOffset;

	// 0		-> translatedValue		-> valueRange
	// 0		-> result - offset		-> range
	float translatedResult = (translatedValue * (targetRange)) / valueRange;
	//cout << "translated " << translatedResult << endl;

	// 0		-> translatedOffset		-> range
	//offset	-> result				-> range+offset
	return translatedResult + targetOffset;
}
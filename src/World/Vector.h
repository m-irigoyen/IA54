#ifndef VECTOR_H_
#define VECTOR_H_

#include <vector>
#include <iostream>

#include "Utilities/MathHelper.h"

/*

*/

class Vector
{
private:
	float x;
	float y;

public:
	Vector(float x = 1.0f, float y = 0.0f);

	// Getters
	void get(float& x, float y) const;
	float getX() const;
	float getY() const;
	
	// Gets the angle of the vector
	float getAngle() const;

	// Setters
	void setX(float x);
	void setY(float y);
	void set(float x, float y);

		// Utility
	// Normalises the vector
	Vector& normalise();	
	// Inverts the vector
	Vector& invert();	
	// Computes the length of the vector
	float length() const;
	// Randomises the vector (but still normalised)
	Vector& randomize();
	
	
	// Normalises v;
	static Vector normalised(const Vector v);	
	// Returns the reverted vector of v
	static Vector inverted(const Vector v);	
	// Returns the normalised right vector of v (UNIMPLEMENTED RIGHT NOW)
	static Vector right(const Vector v);		
	// Gets the vector from point1 to point2
	static Vector getDirection(float x1, float y1, float x2, float y2);
};

#endif



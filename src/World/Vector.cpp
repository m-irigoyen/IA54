#include "Vector.h"

Vector::Vector(float x, float y) : x(x), y(y)
{
	if (this->x == 0.0f && this->y == 0.0f)
		this->randomize();
}

void Vector::get(float & x, float y) const
{
	x = this->x;
	y = this->y;
}

float Vector::getX() const
{
	return this->x;
}

float Vector::getY() const
{
	return this->y;
}

float Vector::getAngle() const
{
	return atan2(this->y,this->x)* 180 / static_cast<float>(M_PI);
}

void Vector::setX(float x)
{
	this->x = x;

	if (this->x == 0.0f && this->y == 0.0f)
		this->randomize();
}

void Vector::setY(float y)
{
	this->y = y;

	if (this->x == 0.0f && this->y == 0.0f)
		this->randomize();
}

void Vector::set(float x, float y)
{
	this->x = x;
	this->y = y;
}

Vector& Vector::normalise()
{
	if (this->length() != 1.0f)
	{
		float l = this->length();
		this->x = this->x / l;
		this->y = this->y / l;
	}
	return *this;
}

Vector& Vector::invert()
{
	this->x *= -1;
	this->y *= -1;
	return *this;
}

float Vector::length() const
{
	return sqrt(pow(this->x, 2) + pow(this->y, 2));
}

Vector & Vector::randomize()
{
	this->setX(random(-1.0f));
	this->setY(random(-1.0f));

	while (this->x == 0.0f && this->y == 0.0f)
	{
		this->setX(random(-1.0f));
		this->setY(random(-1.0f));
	}
	
	this->normalise();

	return *this;
}

Vector Vector::normalised(const Vector v)
{
	return Vector(v.x / v.length(), v.y / v.length());
}

Vector Vector::inverted(const Vector v)
{
	return Vector(v.x * -1, v.y * -1);
}

Vector Vector::right(const Vector v)
{
	//TODO: implement that
	return Vector();
}

Vector Vector::getDirection(float x1, float y1, float x2, float y2)
{
	Vector v(x2 - x1, y2 - y1);
	
	return v;
}

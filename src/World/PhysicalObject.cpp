#include "PhysicalObject.h"

int PhysicalObject::nextId = 0;

PhysicalObject::PhysicalObject(Semantic type, float x, float y) : type(type), posX(x), posY(y), id(nextId)
{
	++nextId;
}


PhysicalObject::~PhysicalObject(void)
{
}

int PhysicalObject::getId()
{
	return id;
}

void PhysicalObject::SetPosition(float x, float y)
{
	this->posX = x;
	this->posY = y;
}

void PhysicalObject::GetPosition(float &x, float &y)
{
	x = this->posX;
	y = this->posY;
}

float PhysicalObject::getX()
{
	return this->posX;
}

float PhysicalObject::getY()
{
	return this->posY;
}

std::vector<float> PhysicalObject::GetPosition()
{
	std::vector<float> ret;
	ret.push_back(this->posX);
	ret.push_back(this->posY);
	return ret;
}

void PhysicalObject::SetSemantic(Semantic type)
{
	this->type = type;
}

Semantic* PhysicalObject::GetSemantic()
{
	return &this->type;
}

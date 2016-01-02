#include "Bodies/Body.h"


Body::Body(Semantic type, float x, float y) : PhysicalObject(type, x, y), bodyType(0)
{

}



void Body::move(float elapsedTime)
{
	this->posX += this->velocity.getXVelocity() * elapsedTime;
	this->posY += this->velocity.getYVelocity() * elapsedTime;
}

void Body::constrainPos(float maxX, float maxY)
{
	if (this->posX < 0)
		this->posX = 0;
	else if (this->posX > maxX)
		this->posX = maxX;

	if (this->posY < 0)
		this->posY = 0;
	else if (this->posY > maxY)
		this->posY = maxY;
}

Perception & Body::getPerception()
{
	return this->perception;
}

void Body::setBodyType(int type)
{
	this->bodyType = type;
}

int Body::getBodyType()
{
	return this->bodyType;
}

Body::~Body(void)
{
}

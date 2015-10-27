#include "Bodies/BodyHybrid.h"
/*
BodyHybrid::BodyHybrid(Semantic type) : BodyEmitter(type), BodyReceptor(type)
{

}

void BodyHybrid::update(int elapsedTime)
{
	BodyReceptor::update(elapsedTime);
	BodyEmitter::update(elapsedTime);
}*/

BodyHybrid::BodyHybrid(Semantic type, float x, float y) : BodyReceptorComposition(type,x,y)
{

}

void BodyHybrid::update(sf::Time elapsedTime)
{
	BodyReceptor::update(elapsedTime);
}

void BodyHybrid::initialise()
{
}

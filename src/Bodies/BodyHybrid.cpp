#include "Bodies/BodyHybrid.h"

BodyHybrid::BodyHybrid(Semantic type, float x, float y) : BodyReceptor_Composition(type,x,y)
{

}

void BodyHybrid::update(sf::Time elapsedTime)
{
	BodyReceptor::update(elapsedTime);
}

void BodyHybrid::initialise()
{
}

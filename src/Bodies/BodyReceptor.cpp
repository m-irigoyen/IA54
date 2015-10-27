#include "Bodies/BodyReceptor.h"

BodyReceptor::BodyReceptor(Semantic type, float x, float y, sf::Time memoryTime) : Body(type,x,y)
{
    this->memoryTime = memoryTime;
}



void BodyReceptor::update(sf::Time elapsedTime)
{

}


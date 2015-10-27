#include "Receptor.h"

Receptor::Receptor()
{

}

void Receptor::onWaveCollision(int emitterId, sf::Time contact, float amplitude)
{
	this->perception.addNewWave(emitterId, contact, amplitude);
}

std::deque<std::pair<sf::Time, float>>* Receptor::getComputedValues()
{
	return &this->computedValues;
}


sf::Time Receptor::getMemoryTime()
{
    return this->memoryTime;
}

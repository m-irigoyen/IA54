#include "Bodies/Receptor.h"

Receptor::Receptor()
{

}

void Receptor::onWaveCollision(int emitterId, sf::Time contact, float amplitude)
{
	this->perception.addNewWave(emitterId, contact, amplitude);
}

void Receptor::onEndOfTransmission(int emitterId, sf::Time contact)
{
	std::cout << "Receptor : terminating transmission " << emitterId << std::endl;
	this->perception.removeWave(emitterId);
}

std::deque<std::pair<sf::Time, float>>* Receptor::getComputedValues()
{
	return &this->computedValues;
}


sf::Time Receptor::getMemoryTime()
{
    return this->memoryTime;
}

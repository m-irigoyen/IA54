#include "Bodies/Receptor.h"

Receptor::Receptor()
{

}

void Receptor::onWaveCollision(int emitterId, sf::Time contact, float amplitude)
{
	this->perceptionWave.addNewWave(emitterId, contact, amplitude);
}

void Receptor::onEndOfTransmission(int emitterId, sf::Time contact)
{
	this->perceptionWave.removeWave(emitterId);
}

std::deque<std::pair<sf::Time, float>>* Receptor::getComputedValues()
{
	return &this->computedValues;
}


sf::Time Receptor::getMemoryTime()
{
    return this->memoryTime;
}

void Receptor::clearPerception()
{
	this->perceptionWave.clear();
	this->computedValues.clear();
}

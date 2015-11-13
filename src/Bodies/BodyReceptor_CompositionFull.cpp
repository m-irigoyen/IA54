#include "Bodies/BodyReceptor_CompositionFull.h"


BodyReceptor_CompositionFull::BodyReceptor_CompositionFull(Semantic type, float x, float y) : BodyReceptor(type, x, y)
{
	this->currentPerception.frequency = -1.0f;
	this->currentPerception.amplitude = 0.0f;
}

	//Receptor functions

// Initialises the receptor
void BodyReceptor_CompositionFull::initialise()
{

}

// Returns what the receptor can make of all it has recieved. This is the wave composition method
WAVE BodyReceptor_CompositionFull::getPerception()
{
	// Resetting values
	this->currentPerception.frequency = 0.0f;
	this->currentPerception.amplitude = 0.0f;

	// For each perceived wave
	for (std::map<int, std::pair<sf::Time, std::pair<float, float>>>::iterator it = this->perception.getWaves()->begin();
		it != this->perception.getWaves()->end();
		++it)
	{
		if (it->second.second.first > 0.0f)	// Frequency isn't null : we can update that wave
		{
			// Update the frequency
			this->currentPerception.frequency += it->second.second.first;

			// Then update the ammplitude
			this->currentPerception.amplitude += it->second.second.second;
		}
    }
	//std::cout << "Returning : " << this->currentPerception.frequency << "," << this->currentPerception.amplitude << std::endl;
	return this->currentPerception;
}

float BodyReceptor_CompositionFull::calculateValueAtT(sf::Time t)
{
	float result = 0.0f;
	for (std::map<int, std::pair<sf::Time, std::pair<float, float>>>::iterator it = this->perception.getWaves()->begin();
		it != this->perception.getWaves()->end();
		++it)
	{
		result += calculateValueAtT(t, it->second.first, it->second.second.first, it->second.second.second);
	}

	return result;
}

// Calculates value for given wave at given time
float BodyReceptor_CompositionFull::calculateValueAtT(sf::Time t, sf::Time firstContact, float frequency, float amplitude)
{
    sf::Time elapsedTime = t - firstContact;
	if (frequency < 0.0f)
	{
		// Frequency hasn't been computed yet
		return 0.0f;
	}
	else
	{
		float period = 2 * PI*frequency;
		while (elapsedTime.asSeconds() > period)
		{
			elapsedTime = sf::seconds(elapsedTime.asSeconds() - static_cast<float>(period));
		}
		return amplitude*sin(elapsedTime.asSeconds() / frequency);
	}
}

void BodyReceptor_CompositionFull::updateComputedValues(sf::Time currentTime)
{
    this->computedValues.push_front(std::pair<sf::Time, float>(currentTime, calculateValueAtT(currentTime)));
    sf::Time differenceTime = currentTime - this->computedValues.back().first;
    //std::cout << "differenceTime " << differenceTime.asSeconds() << std::endl;
    //std::cout << "memoryTime " << differenceTime.asSeconds() << std::endl;
    while(!this->computedValues.empty() && (currentTime - this->computedValues.back().first) > this->memoryTime)
    {
        this->computedValues.pop_back();
    }
}

//Body functions
void BodyReceptor_CompositionFull::update(sf::Time elapsedTime)
{

}

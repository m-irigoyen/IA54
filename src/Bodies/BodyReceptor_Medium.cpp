#include "Bodies/BodyReceptor_Medium.h"


BodyReceptor_Medium::BodyReceptor_Medium(Semantic type, float x, float y) : BodyReceptor(type, x, y)
{
	this->currentPerception.frequency = -1.0f;
	this->currentPerception.amplitude = 0.0f;
}

	//Receptor functions

// Initialises the receptor
void BodyReceptor_Medium::initialise()
{

}

// Returns what the receptor can make of all it has recieved. This is the wave composition method
PerceptionWave::WAVE BodyReceptor_Medium::getPerception()
{
	PerceptionWave::WAVE waves;
	waves.amplitude = 0;
	waves.frequency = 0;

	int nbWaves = 0;

	// For each perceived wave
	for (std::map<int, std::pair<sf::Time, std::pair<float, float>>>::iterator it = this->perceptionWave.getWaves()->begin();
		it != this->perceptionWave.getWaves()->end();
		++it)
	{
		if (it->second.second.first > 0.0f)	// Frequency isn't null : we can update that wave
		{
			waves.frequency += it->second.second.first;
			//std::cout << "COMPUTING FREQUENCY " << it->second.second.first << std::endl;
			waves.amplitude += it->second.second.second;
			++nbWaves;
		}
    }
	//std::cout << "Returning : " << this->currentPerception.frequency << "," << this->currentPerception.amplitude << std::endl;
	waves.amplitude = waves.amplitude / nbWaves;
	waves.frequency = waves.frequency / nbWaves;
	//std::cout << "Nb waves : " << nbWaves << std::endl;
	//std::cout << "Total frequency : " << waves.frequency << std::endl;
	this->currentPerception = waves;
	return this->currentPerception;
}

float BodyReceptor_Medium::calculateValueAtT(sf::Time t)
{
	float result = 0.0f;
	for (std::map<int, std::pair<sf::Time, std::pair<float, float>>>::iterator it = this->perceptionWave.getWaves()->begin();
		it != this->perceptionWave.getWaves()->end();
		++it)
	{
		result += calculateValueAtT(t, it->second.first, it->second.second.first, it->second.second.second);
	}

	return result;
}

// Calculates value for given wave at given time
float BodyReceptor_Medium::calculateValueAtT(sf::Time t, sf::Time firstContact, float frequency, float amplitude)
{
    sf::Time elapsedTime = t - firstContact;
	if (frequency < 0.0f)
	{
		// Frequency hasn't been computed yet
		return 0.0f;
	}
	else
	{
		float period = 2 * (float)M_PI*frequency;
		while (elapsedTime.asSeconds() > period)
		{
			elapsedTime = sf::seconds(elapsedTime.asSeconds() - static_cast<float>(period));
		}
		return amplitude*sin(elapsedTime.asSeconds() / frequency);
	}
}

void BodyReceptor_Medium::updateComputedValues(sf::Time currentTime)
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
void BodyReceptor_Medium::update(sf::Time elapsedTime)
{

}

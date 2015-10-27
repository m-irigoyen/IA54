#include "Perception.h"

Perception::Perception()
{

}

// Adds that new wave to the list
void Perception::addNewWave(int emitterId, sf::Time contact, float amplitude)
{
	std::map<int, std::pair<sf::Time, std::pair<float, float>>>::iterator it = this->percievedWaves.find(emitterId);
	if (it != this->percievedWaves.end())
	{
		// A wave with that id already exists
		sf::Time tempPeriod = (contact - it->second.first);	// Calculating frequency for given wave
		it->second.first = contact;
		it->second.second.first = 1/tempPeriod.asSeconds();	// Setting frequency
		it->second.second.second = amplitude;
	}
	else
	{
		this->percievedWaves.insert
			(
			std::pair<int, std::pair<sf::Time, std::pair<float, float>>>(emitterId, std::pair<sf::Time, std::pair<float, float>>(contact, std::pair<float, float>(-1.0f, amplitude)))
			);

		std::cout << "Perception::addNewWave : first time encountering this id" << std::endl;
	}
}

// Removes given id from the list
void Perception::removeWave(int emitterId)
{
	std::map<int, std::pair<sf::Time, std::pair<float, float>>>::iterator it = this->percievedWaves.find(emitterId);
	if (it != this->percievedWaves.end())
		this->percievedWaves.erase(it);
}

// Return an iterator to the first perception before and after the given time
void Perception::getEncasingIterators(sf::Time t, bool& exactMatch,
        std::map<int, std::pair<sf::Time, std::pair<float, float>>>::iterator& itBefore,
        std::map<int, std::pair<sf::Time, std::pair<float, float>>>::iterator& itAfter)
{
	// Searching for it
    std::map<int, std::pair<sf::Time, std::pair<float, float>>>::iterator it = findByTime(t);

	// Case 1 : found an exact match for t
    if (it != this->percievedWaves.end())   
    {
        exactMatch = true;
        itBefore = it;
        itAfter = it;
        return;
    }
	// Case 2 : t is older than oldest element
    else if (t < (*this->percievedWaves.begin()).second.first) 
    {
        exactMatch = false;
        itBefore = this->percievedWaves.begin();
        itAfter = this->percievedWaves.begin();
        return;
    }
	// Case 3 : t newer than newest perception element
    else if (this->percievedWaves.size() >= 1 &&
		t > (this->percievedWaves.at(this->percievedWaves.size() - 1)).first
            )   
    {
        exactMatch = false;
        itBefore = this->percievedWaves.end();
        itAfter = this->percievedWaves.end();
        return;
    
	}
	else
	{
		// Last case : t must be contained within perceptions. So t > begin, and t < end, but there isn't a wave with the exact time t
		int i = 0;
		// Going through all the perceptions
		for (it = this->percievedWaves.begin(); it != this->percievedWaves.end(); ++it)
		{
			if (t < (*it).second.first)   // We passed t
			{
				exactMatch = false;
				itAfter = it;
				itBefore = --it;
				return;
			}
			++i;
		}
	}
}

std::map<int, std::pair<sf::Time, std::pair<float, float>>>* Perception::getWaves()
{
	return &this->percievedWaves;
}

// Private methods
// Helper function Find a wave by the given time
std::map<int, std::pair<sf::Time, std::pair<float, float>>>::iterator Perception::findByTime(sf::Time t)
{
	// For each perception
	for (std::map<int, std::pair<sf::Time, std::pair<float, float>>>::iterator it = this->percievedWaves.begin();
		it != this->percievedWaves.end();
		++it
		)
	{
		// If the wave has been perceived at the given time, return an iterator to it
		if (it->second.first == t)
			return it;
	}
}

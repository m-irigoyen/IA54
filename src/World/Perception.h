#ifndef PERCEPTION_H_
#define PERCEPTION_H_

/*
*   A Perception object is constructed by the environment to represent all the wavelengths that a Body percieves.
*/

#include <iostream>
#include <map>
#include<vector>
#include <SFML/System/Time.hpp>

struct WAVE_COMPOSITION	// The structure representing a wave
{
	float frequency;
	float amplitude;
};

class Perception
{
private:

	/*!
		This map stores each percieved wave.
		When a wave is percieved and has an unknown emitter id, just add it
		<emitterId, <firstContact, <frequency, amplitude>>>
	*/
	std::map<int, std::pair<sf::Time, std::pair<float, float>>> percievedWaves;	// the list of perceived waves
	std::vector<float> computedValues;	// The resulting values computed for the waves

	//NOTE : Finding one at the exact given time is very unlikely. Maybe implement some sort of delta to search around the wanted time?
	std::map<int, std::pair<sf::Time, std::pair<float, float>>>::iterator findByTime(sf::Time t);	// Helper function Find a wave by the given time


public:
    Perception();

	void addNewWave(int emitterId, sf::Time firstContact, float amplitude);	// Adds that new wave to the list
	void removeWave(int emitterId);	// Removes given id from the list

	/* Return iterators to before and after the given time. There are 4 possibilities :
	1 - there is an exact match. In that case itBefore == itAfter == theElement, and exactMatch = true
	2 - t is smaller than the smallest of our perceived times. In that case exactMatch = false, and itBegin == itEnd == perceivedWaves.begin()
	3 - t is bigger than the bigger of our perceived times. In that case exactMatch = false, and itBegin == itEnd == perceivedWaves.end()
	4 - t is between our biggest and smallest time, but there isn't an exact match. In that case, we return an iterator to the perceptions before (itBefore) and after (itAfter) t
	*/
	void getEncasingIterators(sf::Time t, 
		bool& exactMatch, 
		std::map<int, std::pair<sf::Time, std::pair<float, float>>>::iterator& itBefore,
		std::map<int, std::pair<sf::Time, std::pair<float, float>>>::iterator& itAfter);  

	std::map<int, std::pair<sf::Time, std::pair<float, float>>>* getWaves();	//Getter
};

#endif

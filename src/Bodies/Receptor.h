#ifndef RECEPTOR_H_
#define RECEPTOR_H_

/*
*	Receptor is the abstract interface of all receptor bodies
*/

#include <deque>
#include "World/PerceptionWave.h"


class Receptor
{
protected:
	PerceptionWave perceptionWave;	// The perception of that object
	std::deque<std::pair<sf::Time, float>> computedValues;	// All the values that the receptor computed

    sf::Time memoryTime;	// The time for which the receptor should remember what it perceived


public:
	Receptor();

	virtual void initialise() = 0;	// Initialises the receptor
	virtual PerceptionWave::WAVE getPerception() = 0;    // Returns what the receptor understands of all it has received.
	virtual void onWaveCollision(int emitterId, sf::Time contact, float amplitude);	// Called when the receptor is hit by a wave
	virtual void onEndOfTransmission(int emitterId, sf::Time contact);	// When the emitter stops transmitting, this signals the receptor that it has lost the signal

	virtual float calculateValueAtT(sf::Time t) = 0;    // Calculates resulting value at given time
	virtual float calculateValueAtT(sf::Time t, sf::Time firstContact, float frequency, float amplitude) = 0;    // Calculates value for given wave at given time

	virtual std::deque<std::pair<sf::Time, float>>* getComputedValues();	// Getter
	virtual void updateComputedValues(sf::Time currentTime) = 0;	// Update the perceived values

    virtual sf::Time getMemoryTime();	// getter

	virtual void clearPerception();
};

#endif

#ifndef BODYRECEPTOR_H_
#define BODYRECEPTOR_H_

#include <deque>
#include "Bodies/Body.h"
#include "World/Receptor.h"

#define DEFAULT_MEMORY 5.0f

/*
* Receptor bodies can percieve waves in the world.
* This is the base class for all receptors
*/

class BodyReceptor:  public Body, public Receptor
{
protected:


public:
	BodyReceptor(Semantic type, float x, float y, sf::Time memoryTime = sf::seconds(DEFAULT_MEMORY));

	//Receptor functions
	virtual void initialise() = 0;	// Initialises the receptor
	virtual WAVE_COMPOSITION getPerception() = 0;    // Returns what the receptor can make of all it has recieved. #PHYSICS STUFF
	virtual float calculateValueAtT(sf::Time t) = 0;
	virtual float calculateValueAtT(sf::Time t, sf::Time firstContact, float frequency, float amplitude) = 0;    // Calculates value for given wave at given time

	virtual void updateComputedValues(sf::Time currentTime) = 0;



	//Body functions
    virtual void update(sf::Time elapsedTime) = 0;
};

#endif

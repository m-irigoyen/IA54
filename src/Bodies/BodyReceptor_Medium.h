#ifndef BODYRECEPTOR_MEDIUM_H_
#define BODYRECEPTOR_MEDIUM_H_

#include <math.h>
#include <vector>

#include "Bodies/BodyReceptor.h"
#include "Utilities/MathHelper.h"

/*
* Receptor bodies can percieve waves in the world.
* This is the base class for all receptors
*/

class BodyReceptor_Medium : public BodyReceptor
{
public:
	BodyReceptor_Medium(Semantic type, float x, float y);

	//Receptor functions
	virtual void initialise();	// Initialises the receptor
	virtual WAVE getPerception();    // Returns what the receptor can make of all it has recieved. #PHYSICS STUFF
	virtual float calculateValueAtT(sf::Time t);
	virtual float calculateValueAtT(sf::Time t, sf::Time firstContact, float frequency, float amplitude);    // Calculates value for given wave at given time

    //TODO: coder ça avec la formule des complexes, exprimer l'amplitude en fonction de x,t (page wikipedia interférence)
	virtual void updateComputedValues(sf::Time currentTime);

	//Body functions
	virtual void update(sf::Time elapsedTime);

protected:

	WAVE currentPerception;
};

#endif

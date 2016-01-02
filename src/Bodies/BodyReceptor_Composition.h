#ifndef BODYRECEPTOR_COMPOSITION_H_
#define BODYRECEPTOR_COMPOSITION_H_

#include "Bodies/BodyReceptor.h"
#include "Utilities/MathHelper.h"


#include <math.h>

/*
* Receptor bodies can percieve waves in the world.
* This is the base class for all receptors
*/

class BodyReceptor_Composition : public BodyReceptor
{
public:
	BodyReceptor_Composition(Semantic type, float x, float y);

	//Receptor functions
	virtual void initialise();	// Initialises the receptor
	virtual PerceptionWave::WAVE getPerception();    // Returns what the receptor can make of all it has recieved. #PHYSICS STUFF
	virtual float calculateValueAtT(sf::Time t);
	virtual float calculateValueAtT(sf::Time t, sf::Time firstContact, float frequency, float amplitude);    // Calculates value for given wave at given time

    //TODO: coder ça avec la formule des complexes, exprimer l'amplitude en fonction de x,t (page wikipedia interférence)
	virtual void updateComputedValues(sf::Time currentTime);

	//Body functions
	virtual void update(sf::Time elapsedTime);

protected:

	PerceptionWave::WAVE currentPerception;
};

#endif

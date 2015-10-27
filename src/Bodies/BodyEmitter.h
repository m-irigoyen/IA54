#ifndef BODYEMITTER_H_
#define BODYEMITTER_H_

// This is an interface
/*
*	Emitters can send waves in the world.
	There's nothing to implement in here, everything is already contained in the Emitter interface
*/

#include "Bodies/Body.h"
#include "World/Emitter.h"

class BodyEmitter : public Body, public Emitter
{
public:
	BodyEmitter(Semantic type, float x, float y);

	virtual void initialise();

	// Body methods
    virtual void update(sf::Time elapsedTime);
};

#endif

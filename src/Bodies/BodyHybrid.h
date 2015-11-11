#ifndef BODYHYBRID_H_
#define BODYHYBRID_H_

#include "Bodies/Emitter.h"
#include "Bodies/BodyReceptor_Composition.h"

/*
*	Emitter + receptor
*/

class BodyHybrid: public Emitter, public BodyReceptor_Composition
{
private:

public:
	BodyHybrid(Semantic type, float x, float y);

	virtual void update(sf::Time elapsedTime);
	virtual void initialise();

	~BodyHybrid(void);
};

#endif

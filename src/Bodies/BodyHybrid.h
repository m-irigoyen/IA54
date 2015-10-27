#ifndef BODYHYBRID_H_
#define BODYHYBRID_H_

#include "World/Emitter.h"
#include "Bodies/BodyReceptorComposition.h"

/*
*	Emitter + receptor
*/

class BodyHybrid: public Emitter, public BodyReceptorComposition
{
private:

public:
	BodyHybrid(Semantic type, float x, float y);

	virtual void update(sf::Time elapsedTime);
	virtual void initialise();

	~BodyHybrid(void);
};

#endif

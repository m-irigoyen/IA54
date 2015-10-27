#ifndef BODY_H_
#define BODY_H_

#include <vector>

#include "World/PhysicalObject.h"
#include "World/Perception.h"


/*
*   A Body is a PhysicalObject that can percieve things from the environment, and is linked to an agent.
*   The Agent is the brain, and will give commands to the Body.
*   Here ,the Body can send waves and recieve Perceptions from the environment.
*/

class Body:  public PhysicalObject
{
private:

public:
	Body(Semantic type, float x, float y);

	virtual void update(sf::Time elapsedTime) = 0;

	~Body(void);
};

#endif

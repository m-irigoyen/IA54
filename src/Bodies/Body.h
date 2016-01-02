#ifndef BODY_H_
#define BODY_H_

#include <vector>

#include "World/PhysicalObject.h"
#include "World/Perception.h"
#include "World/Velocity.h"


/*
*   A Body is a PhysicalObject that can percieve things from the environment, and is linked to an agent.
*   The Agent is the brain, and will give commands to the Body.
*   Here ,the Body can send waves and recieve Perceptions from the environment.
*/

class Body:  public PhysicalObject
{
protected:
	Perception perception;
	Velocity velocity;

	void move(float elapsedTime);

	int bodyType;	// This type is strictly used for displaying different colors depending on agent types.
	

public:
	Body(Semantic type, float x, float y);

	virtual void update(sf::Time elapsedTime) = 0;
	// constrains the body's position between 0 and the maximum given for each axis
	void constrainPos(float maxX, float maxY);

	Perception& getPerception();

	void setBodyType(int type);
	int getBodyType();


	~Body(void);
};

#endif

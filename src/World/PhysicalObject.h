#ifndef PHYSICALOBJECT_H_
#define PHYSICALOBJECT_H_

#include <vector>

#include "Semantic.h"
#include <SFML/System/Time.hpp>

/*
*   The PhysicalObject is the base class for all the object in the simulation.
*   Everything that exists in the environment is derived from a PhysicalObject.

*   PhysicalObjects are defined by their Semantic.
	They also have a position, and an id
*/

class PhysicalObject
{
protected:
	Semantic type;
	float posX;
	float posY;

	const int id;
	static int nextId;

public:
	PhysicalObject(Semantic type, float x, float y);

	// Getter, setters
	int getId();

	virtual void SetPosition(float x, float y);
	virtual void GetPosition(float &x, float &y);
	virtual float getX();
	virtual float getY();

	virtual std::vector<float> GetPosition();

	virtual void SetSemantic(Semantic type);
	virtual Semantic* GetSemantic();

    // updates the object every frame
	virtual void update(sf::Time elapsedTime) = 0;

	~PhysicalObject(void);
};

#endif


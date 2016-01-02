#ifndef VELOCITY_H_
#define VELOCITY_H_

/*
Force class. This is where forces are applied and resolved to objects
*/

#include <vector>
#include <iostream>

#include "Vector.h"

// Defines for the code.
#define REST_DECELERATION 0.05f
#define GRAVITY 9.81f

using namespace std;

class Velocity
{
public:
	Velocity();
	~Velocity();

		// Force functions
	//FIXME: weird functions in there. Remove the useless ones.
	// Won't be applied until resolveForces is called
	void addXForce(float force);
	// Won't be applied until resolveForces is called
	void addYForce(float force);
	// Adds v * unit as a force. Won't be applied until resolveForces is called
	void addForce(Vector v, float unit = 1.0f);
	// Adds the given x and y forces. Won't be applied until resolveForces is called
	void addForce(float xForce, float yForce);	// Add a force to the vector.

		// Deceleration functions
	void tendToRestX(float deceleration = REST_DECELERATION); //TODO: implement that
	void tendToX(float targetVelocity, double factor = 1); //TODO: implement that
	void tendToY(float targetVelocity, double factor = 1); //TODO: implement that
	//QUESTION : Are those 2 necessary when we have the above?
	void tendTo(bool x, float factor);	// Generate a force so that velocity tends to factor*m_maxSpeed on the desired axis
	void tendTo(float x, float y, float factor);	// Generate a force so that velocity tends to factor*m_maxSpeed

		// Resolving forces
	// Resolves the forces currently waiting.
	void resolveForces(float dt, bool applyGravity = false);	
	// Clears current velocity, then resolve forces
	void resolveForcesWithoutVelocity(float dt);

	// Returns true if the object is immobile
	bool immobile();	

		// Velocity setters
	void setVelocity(float xVelocity, float yVelocity);
	void setXVelocity(float xVelocity);
	void setYVelocity(float yVelocity);
	void setForce(float xForces, float yForces);

		//Getters
	// returns current velocity
	void getVelocity(float& xVelocity, float& yVelocity);	// Returns the vectors velocity
	// returns current velocity in Vector form
	Vector getVelocity();
	// returns current Y velocity
	float getYVelocity();
	// returns current X velocity
	float getXVelocity();

	// returns the forces that will be applied on the next resolution
	void getForce(float& xForces, float& yForces);
	// returns the forces that will be applied on the next resolution
	Vector getForce();
	// returns the current direction
	Vector getDirection();


protected:
	// Current velocity
	float m_vel_x;
	float m_vel_y;

	// Forces to be resolved
	float m_for_x;
	float m_for_y;

	// maximum velocity
	float maxVelocity;

};

#endif
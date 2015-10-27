#ifndef PROBLEMROCKET_H_
#define PROBLEMROCKET_H_

#include <iostream>
#include "Problem.h"
#include "Utilities/MathHelper.h"
#include <SFML/Graphics.hpp>

#define MARS_GRAVITY 10			// Gravity acceleration in meters/seconds
#define THRUSTER_STRENGTH 12	// Strength of each thruster in meters/seconds

#define ANGLE_OFFSET 90	// Offset to have 0° be up

/*
* The Problem class creates and run the problem to be solved. (pendulum, drone, etc)
*/

using namespace std;

class ProblemRocket : public Problem
{
protected:
	sf::Texture rocketTexture;
	sf::Sprite rocketSprite;

	// World dimensions
	int worldWidth;
	int worldHeight;

	// Rocket coordinates
	double rocketX;
	double rocketY;
	int rocketAngle;

	// Rocket information
	double hSpeed;
	double vSpeed;
	bool hasLanded;
	bool hasCrashed;

	// Engines
	int enginePower;

	// PRIVATE FUNCTIONS
	bool collides(double x, double y);	// Checks if the given position is colliding with terrain
	bool correctLanding(double hSpeed, double vSpeed, int angle);

	// Physics stuff
	// Get the hForce and vForce to be applied, given the engine power and angle of the rocket
	void getThrustersForce(int angle, int powerLeft, double& hForce, double& vForce);


public:
	ProblemRocket();

	virtual void run(sf::Time elapsedTime);	// Updating the problem
	virtual void draw(sf::RenderWindow* problemWindow);
	virtual void init();	// Running the problem

	// Rocket handling
	void setPower(int power);
	void addPower(int powerOffset);
	void setAngle(int angle);
	void addAngle(int angleOffset);
};

#endif


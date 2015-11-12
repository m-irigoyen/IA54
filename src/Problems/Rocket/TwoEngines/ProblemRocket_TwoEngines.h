#ifndef PROBLEMROCKET_TWOENGINES_H_
#define PROBLEMROCKET_TWOENGINES_H_

#include <iostream>
#include <SFML/Graphics.hpp>

#include "Problems/Rocket/ProblemRocket.h"
#include "Utilities/MathHelper.h"


// World values
#define MARS_GRAVITY 4			// Gravity acceleration in meters/seconds
#define SIZE_DEFAULT_WIDTH 100
#define SIZE_DEFAULT_HEIGHT 100

// HUD stuff
#define HUD_SIZE_THRUSTER 0.5

// Rocket values
#define THRUSTER_STRENGTH 10	// Strength of each thruster in meters/seconds
#define ANGLE_OFFSET 90	// Offset to have 0� be up

/*
* The Problem class creates and run the problem to be solved. (pendulum, drone, etc)
*/

enum AGENTTYPE_ROCKET_TWO
{
	ROCKET_HS_TWO_DEFAULT,
	ROCKET_HS_TWO_DIRECTION,
	ROCKET_HS_TWO_POWER
};

using namespace std;

class ProblemRocket_TwoEngines : public ProblemRocket
{
protected:
	sf::RectangleShape hud_engineFire;

	// PRIVATE FUNCTIONS
	// Rocket

	// PRIVATE FUNCTIONS
	// Physics stuff
	virtual void getThrustForce(double& hForce, double& vForce);	// Compute the thrust generated by the engines with current angle and current enginePowers values

	virtual void checkEvents(sf::RenderWindow* window);	// Checks for user input on the problem window
	virtual bool handleEvent(sf::RenderWindow* window, sf::Event event);	// Returns true if event has been dealt with

			//Rocket control
	virtual void resolveRocketPowerChange();	// Based on the desired power and rotation, resolve what's happening
	virtual void resolveRocketAngleChange();

	// Agent influence
	void resolveInfluences();

public:
	ProblemRocket_TwoEngines(float waveAmplLossPerSec = 0.0f);

	virtual void run(sf::Time elapsedTime);	// Updating the problem
	virtual void draw(sf::RenderWindow* problemWindow);
	virtual void clean();
	virtual void init();	// init
	virtual void initGraphics(std::vector<sf::Font>* fonts);

	// Rocket handling : these modify the rocket directly.

	// Agents
};

#endif


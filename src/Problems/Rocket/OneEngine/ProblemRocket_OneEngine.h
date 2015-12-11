#ifndef PROBLEMROCKET_ONEENGINE_H_
#define PROBLEMROCKET_ONEENGINE_H_

#include <iostream>
#include <SFML/Graphics.hpp>

#include "Problems/Rocket/ProblemRocket.h"
#include "Utilities/MathHelper.h"


// Problem values
//TODO: remove those.
#define PROBLEMROCKET_ONE_PROBLEM_MAXANGLE 45.0f	// The maximum angle the agents will deviate from 0

#define PROBLEMROCKET_ONE_PROBLEM_MAXHSPEED 20.0f
#define PROBLEMROCKET_ONE_PROBLEM_MAXVSPEED 40.0f


/*
* The Rocket problem represents a rocket with only one thruster. The rocket can be controlled by rotating it, and setting its engine power.
*/

enum AGENTTYPE_ROCKET_ONE
{
	ROCKET_ONE_RECEPTOR,
	ROCKET_ONE_DIRECTION,	// Direction agents guide the rocket towards the landing zone
	ROCKET_ONE_ALTITUDE,	// These agents handle the rocket's altitude
							
							// Stabilizer agents stabilize the rocket
	ROCKET_ONE_STABILIZER_HSPEED,	// Regulates the rocket's horizontal speed
	ROCKET_ONE_STABILIZER_VSPEED,	// Regulates the rocket's vertical speed
};

using namespace std;

class ProblemRocket_OneEngine : public ProblemRocket
{
protected:
	// User interface
	sf::RectangleShape hud_engineFire;


	// PRIVATE FUNCTIONS
	// Physics stuff
	virtual void getThrustForce(float& hForce, float& vForce);	// Compute the thrust generated by the engines with current angle and current enginePowers values

	virtual void checkEvents(sf::RenderWindow* window);	// Checks for user input on the problem window
	virtual bool handleEvent(sf::RenderWindow* window, sf::Event event);	// Returns true if event has been dealt with

	//Rocket control
	virtual void initUserControl(bool userControl);

	virtual void resolveRocketPowerChange();	// Based on the desired power and rotation, resolve what's happening
	virtual void resolveRocketAngleChange();

	// Agent influence
	void resolveInfluences();


public:
	ProblemRocket_OneEngine(float waveAmplLossPerSec = 0.0f);

	//virtual void run(sf::Time elapsedTime);	// Updating the problem
	virtual void draw(sf::RenderWindow* problemWindow);
	virtual void clean();
	virtual void init();	// init 
	virtual void initGraphics(std::vector<sf::Font>* fonts);

	// Agents
};

#endif


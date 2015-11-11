#ifndef PROBLEMROCKET_HS_ONEENGINE_H_
#define PROBLEMROCKET_HS_ONEENGINE_H_

#include <iostream>
#include "Problems/Problem.h"
#include "Utilities/MathHelper.h"
#include <SFML/Graphics.hpp>

// World values
#define MARS_GRAVITY 4			// Gravity acceleration in meters/seconds
#define SIZE_DEFAULT_WIDTH 100
#define SIZE_DEFAULT_HEIGHT 100

// HUD stuff
#define HUD_SIZE_THRUSTER 0.5

// Rocket values
#define THRUSTER_STRENGTH 8	// Strength of each thruster in meters/seconds


// Wave values
#define ROCKET_WAVE_AMPLITUDE_OFFSET 10.0f
#define ROCKET_WAVE_AMPLITUDE_RANGE 10.0f

#define ROCKET_WAVE_FREQUENCY_OFFSET 10.0f
#define ROCKET_WAVE_FREQUENCY_RANGE 10.0f

// Problem values
#define PROBLEMROCKET_HS_ONE_PROBLEM_MAXANGLE 25.0f	// The maximum angle the agents will deviate from 0
#define PROBLEMROCKET_HS_ONE_PROBLEM_MAXDISTANCE 150.0f	// The threshold in distance considerations

#define PROBLEMROCKET_HS_ONE_PROBLEM_MAXHSPEED 10.0f
#define PROBLEMROCKET_HS_ONE_PROBLEM_MAXVSPEED -30.0f

// Rocket specs
#define PROBLEMROCKET_HS_ONE_SPECS_POWER_MAX 100	// The maximum power the rocket can have


/*
* The Rocket problem represents a rocket with only one thruster. The rocket can be controlled by rotating it, and setting its engine power.
*/

enum AGENTTYPE_ROCKET_HS_ONE
{
	ROCKET_HS_ONE_DEFAULT,
	ROCKET_HS_ONE_DIRECTION,
	ROCKET_HS_ONE_REGULATOR,
	ROCKET_HS_ONE_STABILIZER
};

using namespace std;

class ProblemRocket_HS_OneEngine : public Problem
{
protected:
	// Problem related values
	int numberOfAgents;

	// hud stuff
	sf::Texture hud_rocketTexture;
	sf::Sprite hud_rocketSprite;

	// Rocket coordinates
	double rocketX;
	double rocketY;
	double rocketAngle;

	// Rocket information
	double hSpeed;
	double vSpeed;
	bool hasLanded;
	bool hasCrashed;

	// Agents influence
	double desiredRotationChange;
	double desiredPowerChange;

	// Engines
	int enginePower;

	// User control
	bool userControlled;

	// User interface
	sf::Text hud_hSpeed;
	sf::Text hud_vSpeed;
	sf::Text hud_angle;
	sf::Text hud_power;

	sf::RectangleShape hud_engineFire;


	// PRIVATE FUNCTIONS
	// Rocket
	void resetRocket(int x = -1, int y = -1);	// Reset rocket at given position

	// Physics stuff
	// Get the hForce and vForce to be applied, given the engine power and angle of the rocket
	void getThrustersForce(double angle, int powerLeft, double& hForce, double& vForce);

	virtual void checkEvents(sf::RenderWindow* window);	// Checks for user input on the problem window

	double constrainAngle(double angle);	// Constrains given angle between 0 and 359 degrees

public:
	ProblemRocket_HS_OneEngine(float waveAmplLossPerSec = 0.0f);

	//TODO: load terrain
	virtual void loadTerrain(std::string path = "Default");
	virtual void saveTerrain(std::string path);

	virtual void run(sf::Time elapsedTime);	// Updating the problem
	virtual void draw(sf::RenderWindow* problemWindow, std::vector<sf::Font>* fonts);
	virtual void clean();
	virtual void init();	// init 
	virtual void initGraphics(std::vector<sf::Font>* fonts);

	// Rocket handling : these modify the rocket directly.
	void setPower(int power);
	void addPower(int powerOffset);
	void setAngle(double angle);
	void addAngle(double angleOffset);

	// Agents
	void setNumberOfEmitters(int nb);
	int getNumberOfEmitters();
	void getProblemData(double& x, double& y, double& hSpeed, double& vSpeed, double& angle, double& power, double& distanceToGround, double& distanceToCenterOfLandingZone);
};

#endif


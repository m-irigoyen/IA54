#ifndef PROBLEMROCKET_H_
#define PROBLEMROCKET_H_

#include <iostream>
#include "Problem.h"
#include "Utilities/MathHelper.h"
#include <SFML/Graphics.hpp>

// World values
#define MARS_GRAVITY 4			// Gravity acceleration in meters/seconds
#define SIZE_DEFAULT_WIDTH 100
#define SIZE_DEFAULT_HEIGHT 100

// HUD stuff
#define HUD_SIZE_THRUSTER 0.5

// Rocket values
#define THRUSTER_STRENGTH 10	// Strength of each thruster in meters/seconds
#define ANGLE_OFFSET 90	// Offset to have 0° be up


// Wave values
#define ROCKET_WAVE_AMPLITUDE_OFFSET 10.0f
#define ROCKET_WAVE_AMPLITUDE_RANGE 10.0f

#define ROCKET_WAVE_FREQUENCY_OFFSET 10.0f
#define ROCKET_WAVE_FREQUENCY_RANGE 10.0f

// Problem values
#define ROCKET_PROBLEM_MAXANGLE 45.0f	// The maximum angle the agents will deviate from 0
#define ROCKET_PROBLEM_MAXDISTANCE 500.0f	// The threshold in distance considerations

// Rocket specs
#define ROCKET_SPECS_POWER_MAX 100	// The maximum power the rocket can have


/*
* The Rocket problem represents a rocket with only one thruster. The rocket can be controlled by rotating it, and setting its engine power.
*/

enum AGENTTYPE_ROCKET
{
	ROCKET_DEFAULT,
	ROCKET_DIRECTION,
	ROCKET_ALTITUDE
};

using namespace std;

class ProblemRocket : public Problem
{
protected:
	// Problem related values
	int numberOfAgents;

	// hud stuff
	sf::Texture hud_rocketTexture;
	sf::Sprite hud_rocketSprite;

	// World 
	int worldWidth;
	int worldHeight;
	int worldFlatZone1;
	int worldFlatZone2;

	vector<pair<int, int>> terrain;	// The terrain. Just specify points, the collision and drawing is automatic

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

	bool collides(double x, double y);	// Checks if the given position is colliding with terrain
	bool correctLanding(double hSpeed, double vSpeed, double angle);	// Checks if the rocket landed correctly
	double getTerrainPoint(double x, pair<int, int> p1, pair<int, int> p2);	// Gets the Y coordinate for the given X, with p1.x <=x and p2.x >= x
	vector<pair<int, int>>::iterator getPointBefore(double x);	// Returns the point contained in this->terrain with closest smallest x compared to given x parameter

	// Physics stuff
	// Get the hForce and vForce to be applied, given the engine power and angle of the rocket
	void getThrustersForce(double angle, int powerLeft, double& hForce, double& vForce);

	void checkEvents(sf::RenderWindow* window);	// Checks for user input on the problem window

	double constrainAngle(double angle);	// Constrains given angle between 0 and 359 degrees

public:
	ProblemRocket(float waveAmplLossPerSec = 0.0f);

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

	double getAngle();

	// Agents
	void setNumberOfEmitters(int nb);
	int getNumberOfEmitters();
	void getProblemData(double& x, double& y, double& hSpeed, double& vSpeed, double& angle, double& power, double& distanceToGround, double& distanceToCenterOfLandingZone);
};

#endif


#ifndef PROBLEMROCKET_HS_TWOENGINES_H_
#define PROBLEMROCKET_HS_TWOENGINES_H_

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
#define THRUSTER_STRENGTH 10	// Strength of each thruster in meters/seconds
#define ANGLE_OFFSET 90	// Offset to have 0° be up

/*
* The Problem class creates and run the problem to be solved. (pendulum, drone, etc)
*/

enum AGENTTYPE_ROCKET_HS_TWO
{
	ROCKET_HS_TWO_DEFAULT,
	ROCKET_HS_TWO_DIRECTION,
	ROCKET_HS_TWO_POWER
};

using namespace std;

class ProblemRocket_HS_TwoEngines : public Problem
{
protected:
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
	int enginePowerRight;
	int enginePowerLeft;

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
	void getThrustersForce(double angle, int powerLeft, int powerRight, double& hForce, double& vForce);

	void checkEvents(sf::RenderWindow* window);	// Checks for user input on the problem window

public:
	ProblemRocket_HS_TwoEngines(float waveAmplLossPerSec = 50.0f);

	virtual void loadTerrain(std::string path = "Default");
	virtual void saveTerrain(std::string path);

	virtual void run(sf::Time elapsedTime);	// Updating the problem
	virtual void draw(sf::RenderWindow* problemWindow, std::vector<sf::Font>* fonts);
	virtual void clean();
	virtual void init();	// init
	virtual void initGraphics(std::vector<sf::Font>* fonts);

	// Rocket handling : these modify the rocket directly.
	void setPowerRight(int power);
	void setPowerLeft(int power);

	void addPowerRight(int powerOffset);
	void addPowerLeft(int powerOffset);
	void setAngle(double angle);
	void addAngle(double angle);

	// Agents
};

#endif


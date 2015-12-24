#ifndef PROBLEMROCKET_H_
#define PROBLEMROCKET_H_

#include <string>

#include "Problems/Problem.h"
#include "Problems/Rocket/ProblemRocket_Terrain.h"
#include "Problems/Rocket/ProblemRocket_Trajectory.h"
#include "Utilities/FilePaths.h"

// Rocket specs
#define PROBLEMROCKET_ROCKET_THRUST_BASE 8.0f
#define PROBLEMROCKET_ROCKET_POWER_MAX 100.0f

// GUI
#define PROBLEMROCKET_GUI_ANGLE_OFFSET 90.0f
#define PROBLEMROCKET_GUI_SIZE_THRUSTER 0.5f

using namespace std;

class ProblemRocket : public Problem
{
protected:
	// Terrain
	ProblemRocket_Terrain terrain;
	ProblemRocket_Trajectory trajectories;

	// Problem status
	float problemSpeed;

	// Rocket current values
	vector<float> rocket_engineThrust;	// How much thrust does each engine generate
	vector<float> rocket_enginesPower;	// Percentage of power of the given engine, between 0 (no thrust) and 100 (max thrust)
	float rocket_angle;
	float rocket_hSpeed;
	float rocket_vSpeed;

	// Rocket position
	float rocket_x;
	float rocket_y;

	// Rocket status
	bool hasLanded;
	bool hasCrashed;
	bool hasGoneMissing;

	// Rocket control
	// Those values determine how fast the rocket can rotate, and how fast the engine's power can vary. Values < 0 mean the change is immediate.
	float rocket_rotationRate;
	float rocket_engineChangeRate;
	bool useRelativeChange;	// If true, rotation and power are resolved using desiredRotationChange and desiredPowerChange. If false, they are resolved with desiredRotation and desiredPower. It's just a matter of choosing how the agents work : with hard values, or with offset changing.

	float desiredRotation;	// The influence towards which to go. If useGradualChange == true, that's treated as an offset to apply to the current value. Else, we set the rotation/power directly to the desired value
	vector<float> desiredPower;
	float rotationChange;	// The result of all influences on rotation change
	vector<float> powerChange;	// The result of all influences on power change

	// GUI stuff
	sf::Texture hud_rocketTexture;
	sf::Sprite hud_rocketSprite;
	sf::Text hud_text;
	
	bool userControlled;	// When this is true, shuts down agent influences and allow the user to directly control the rocket

		// Helper functions
	// Terrain checking
	virtual bool correctLanding(float hSpeed, float vSpeed, float angle);	// Returns true if those value make a correct landing
	virtual void moveRocket(sf::Time elapsedTime, float hEnginesForce, float vEnginesForce);
	virtual void getThrustForce(float& hForce, float& vForce) = 0;	// Compute the thrust generated by the engines with current angle and current enginePowers values

	// Event checking
	virtual void checkEvents(sf::RenderWindow* window);	// Checks for user input
	virtual bool handleEvent(sf::RenderWindow* window, sf::Event event);	// Returns true if event has been dealt with

	// Rocket control
	
	virtual void initUserControl(bool useControl) = 0;
	// returns the given angle constrained so 0 <= angle < 360
	virtual float constrainAngle(float angle);	// Constrains given angle between 0 and 359 degrees
	virtual float constrainAngleChange(float currentAngle, float desiredRotation);
	virtual float constrainPower(float power);
	virtual float constrainPowerChange(float currentPower, float desiredPowerChange);

	virtual void resolveRocketPowerChange() = 0;	// Based on the desired power and rotation, resolve what's happening
	virtual void resolveRocketAngleChange() = 0;

	virtual void resetDesiredChanges();

	// Agent influence
	virtual void resolveInfluences() = 0;
	

public:
	// Constructors
	ProblemRocket(float waveAmplLossPerSec = 0.0f, bool useAttenuation = false);

	// Running the problem
	// TO RUN THE PROBLEM : call getThrustersStrength to get the current force applied to the rocket. Then call moveRocket.
	virtual void run(sf::Time elapsedTime);			// Run the problem
	virtual void clean();
	virtual void resetRocket();	// Resets the rocket to its starting position, with starting hSpeed and vSpeed

	// Init
	virtual void init() = 0;
	virtual void initGraphics(std::vector<sf::Font>* fonts);
	virtual void setRocketRotationRate(float rocketRotationRate);
	virtual void setRocketengineChangeRate(float engineChangeRate);

	// GUI
	virtual void draw(sf::RenderWindow* window);	// Draw the problem on the given window

	// Terrain
	virtual void loadTerrain(string path);
	virtual void generateTerrain(int width = -1, int height = -1);
	
	// Getters
	ProblemRocket_Terrain* getTerrain();
		// Rocket data
	bool getHasLanded();
	bool getHasCrashed();
	bool getHasGoneMissing();
	void getRocketPosition(float& rocketX, float& rocketY);
	void getRocketSpeed(float& rocketHSpeed, float& rocketVSpeed);
	float getRocketAngle();
	vector<float>* getRocketEnginesPower();
	float getRocketDistanceToGround();
	float getRocketDistanceToLandingZoneCenter();
	float getLandingZoneSize();
	float getPowerMax();
	void getHighestPointBeforeLanding(float& pointX, float& pointY);
	void getSafeLandingSpecs(float& maxHSpeed, float& maxVSpeed, float& maxAngle);

	// Rocket control
	void setPower(int engineNumber, float power);
	void setAngle(float angle);
	bool getUseRelativeChange();
	void setUseRelativeChange(bool relativeChange);

	bool getUserControlled();

	// Agent influence
	void setDesiredPower(int engineNumber, float power);
	void setDesiredAngle(float angle);
};


#endif
#ifndef PROBLEM_H_
#define PROBLEM_H_

#include <SFML/System/Time.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include "pugixml\pugixml.hpp"

#include "Utilities/MathHelper.h"

/*
* The Problem class creates and run the problem to be solved. (pendulum, drone, etc)
*/

enum PROBLEM_TYPE
{
	NONE,
	POINTER,
	DRONE,
	ROCKET_ONE,
	ROCKET_TWO,
	ROCKET_TERRAINEDITOR
};

class Problem
{
protected:
	// Physics stuff
	float waveAmplLossPerSec;
	bool useWaveAttenuation;

	// Problem management
	bool problemLive; // True if the problem is currently running
	bool pause;			// True if the problem is paused.
	
	// Agents stuff
	int numberOfEmitters;
	int numberOfReceptors;

	// Agents influence
	float wave_amplitude_offset;
	float wave_amplitude_range;
	float wave_frequency_offset;
	float wave_frequency_range;

	// Flag used to ask the simulator to reset the agents
	bool resetAgents;


public:
	// Constructors
	Problem(float waveAmplLossPerSec = 0.0f, bool useAttenuation = false);

	// Running the problem
	virtual void run(sf::Time elapsedTime) = 0;			// Run the problem
	virtual void clean() = 0;

	// Init
	virtual void init() = 0;
	virtual void initGraphics(std::vector<sf::Font>* fonts) = 0;

	// GUI
	virtual void draw(sf::RenderWindow* window) = 0;	// Draw the problem on the given window
	virtual void checkEvents(sf::RenderWindow* window);	// Checking for events
	virtual bool handleEvent(sf::RenderWindow* window, sf::Event event);	// Returns true if event has been dealt with
	
	// Getters
	float getAmplitudeLoss();
	virtual bool getProblemLive();
	virtual bool isUsingAttenuation();
	virtual int getNumberOfEmitters();
	virtual int getNumberOfReceptors();
	virtual bool getResetAgent();

	// Problem data
	float getWaveAmplitudeOffset();
	float getWaveAmplitudeRange();
	float getWaveFrequencyOffset();
	float getWaveFrequencyRange();
	virtual bool getPause();

	// Setters
	virtual void setNumberOfEmitters(int nb);
	virtual void setNumberOfReceptors(int nb);
	virtual void setPause(bool pause);

};

#endif


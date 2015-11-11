#ifndef PROBLEM_H_
#define PROBLEM_H_

#include <SFML/System/Time.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

#include "pugixml\pugixml.hpp"

/*
* The Problem class creates and run the problem to be solved. (pendulum, drone, etc)
*/

enum PROBLEM_TYPE
{
	NONE,
	POINTER,
	DRONE,
	ROCKET_HS_ONE,
	ROCKET_HS_TWO
};

class Problem
{
protected:
	float waveAmplLossPerSec;
	bool problemLive; // True if the problem is currently running
	bool useWaveAttenuation;

public:
	Problem(float waveAmplLossPerSec = 0.0f, bool useAttenuation = false);
	virtual void run(sf::Time elapsedTime) = 0;			// Run the problem
	virtual void draw(sf::RenderWindow* window, std::vector<sf::Font>* fonts) = 0;	// Draw the problem on the given window
	virtual void init() = 0;
	virtual void clean() = 0;
	virtual void initGraphics(std::vector<sf::Font>* fonts) = 0;

	virtual float getAmplitudeLoss();
	virtual bool getProblemLive();
	virtual bool isUsingAttenuation();
};

#endif


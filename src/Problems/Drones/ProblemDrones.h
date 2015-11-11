#ifndef PROBLEMDRONES_H_
#define PROBLEMDRONES_H_

/**
* The Problem class creates and run the problem to be solved. (pendulum, drone, etc)
* This one is aimed at solving the drone problem.
* The drones are simulated on Unity. The communication between the physical drones (Unity) and the agents (this program) is done via sockets.
*
* The waves can transmit 2 informations : amplitude and frequency. That means 2 different informations
*	- With the frequency, we will transmit both the current behaviour, and the behaviour information 1.
*		For that to work, we assume that each behaviour will be encoded on a given 1khz frequency range.
*		We use a 1khz margin between each behaviour to reduce noise sensitivity.
*	- On the amplitude, we transmit the behaviour information 2.
*
* Each behaviour will use the 2 informations to give the correct behaviour.
*
* We suppose here that each drone will intrinsequely know the position of the behaviour's center, and/or that this position will not
* be transmitted via waves.
*
* In a first iteration of the model, we suppose the drones only listen to waves, they don't emit themselves.
* We will then implement a model where drones can override the basic behaviour by broadcasting alert messages.
*/

#include <iostream>
#include <deque>
#include <string>
#include "Problems/Problem.h"
#include "Utilities/Network.h"
//#include <SFML/Graphics.hpp>

#define FREQUENCY_OFFSET_D 10
#define FREQUENCY_RANGE_D 1000
#define FREQUENCY_MARGIN_D 100
#define AMPLITUDE_OFFSET_D 1
#define AMPLITUDE_RANGE_D 1

using namespace std;

struct droneOrder
{
	float xOffset;
	float yOffset;
	float zOffset;
};

struct pos3
{
	float xPos;
	float yPos;
	float zPos;
};

enum DRONE_BEHAVIOURS
{
	hover,		// Default behaviour : just hover and don't do anything
	circle,		// Form a circle around the target
	triangle,	// Form a triangle with the target at the middle of its base
	wall		// Form a wall in front of the target
};

class ProblemDrones : public Problem
{
protected:
	std::map<int, DRONE_BEHAVIOURS> behaviourTable;	// Lookup table for behaviours : <frequency, behaviour>
	Network unityConnection;
	deque<string> messages;

	map<int, droneOrder> droneCommands;	// Orders that the Problem will transmit to Unity
	map<int, pos3> dronePositions;

	int nbDrones;	// The number of drones


	
public:
	ProblemDrones(std::map<int,DRONE_BEHAVIOURS> behaviourTable, int numberOfDrones);

	virtual void run(sf::Time elapsedTime);	// run the whole thing
	virtual void replicatePositions();

	bool init(int portNumber = 13374);	// Inits connection with Unity

	int getNbDrones();
	void setNbDrones(int nbDrones);

	pos3 getPos(int droneId);
	void setPos(int droneId, pos3 pos);

	void setDroneOrder(int droneId, droneOrder order);	// This is just to centralize message sending. ultimately, each drone should have its own network socket

	virtual DRONE_BEHAVIOURS getBehaviour(int frequency);	// For a given frequency, get the corresponding behaviour
	virtual DRONE_BEHAVIOURS getBehaviour(float frequency);	//
};

#endif


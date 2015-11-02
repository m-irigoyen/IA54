#ifndef SIMULATOR_H_
#define SIMULATOR_H_

#include <vector>
#include <chrono>
#include <iostream>

#include "Graphics/GraphicView.h"

// Pointer problem
#include "Agents/AgentEmitterProblemPointer.h"
#include "Agents/AgentReceptorProblemPointer.h"

// Drone problem
#include "Agents/AgentHybridProblemDrones.h"
#include "Bodies/BodyHybrid.h"

// Rocket problem
#include "Agents/AgentEmitterRocket.h"
#include "Agents/AgentReceptorRocket.h"
#include "Agents/AgentRocketTest.h"


/*
*   The Simulator is the main class of the project.
*   The Simulator is created with an instance of the Problem class. The Problem modelises what it is that the Simulator is trying
*   to solve : drone, pendulum, slink, etc.
*   The Simulator then inits the program, creates the world and the agents, links the agents to their bodies, links the agents
*   to the Problem accordingly.
*
*   It then runs the whole thing via the Run function.
*/


class Simulator
{
private:
	GraphicView SFMLView;		// GUI
	sf::RenderWindow* window;	// Reference to the window
	
	World world;				// The environment
	std::vector<Agent*> agents; // The agents

	sf::Clock simulationClock;	// The clock for the simulation
	bool finishSimulation;		// Flag : exit application
	bool frameFlag;				// Flag : Simulate/render frame

	//User interface stuff, only used by the ProblemPointer
	Body* selectedBody;

		// Problem
	//ProblemPointer* problem;   // The instance of the pointer problem.
	//ProblemDrones* problem;   // The instance of the drone problem.
	ProblemRocket* problem;   // The instance of the drone problem.

	PROBLEM_TYPE problemType;	// The type of the current problem

public:
	Simulator();
	void init();	// Initialise everything. Is called before run()
	void initProblem(PROBLEM_TYPE newProblem);

    // Creates an agent at given position, then add him to the agent list
	void addEmitter(float xPos, float yPos);
	void addReceptor(float xPos, float yPos);
	void addHybrid(float xPos, float yPos);

	void checkEvents();					// Check user events
	void run(sf::Time refreshRate);		// Simulation loop

	~Simulator(void);
};

#endif

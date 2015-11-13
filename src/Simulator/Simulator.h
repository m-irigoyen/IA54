#ifndef SIMULATOR_H_
#define SIMULATOR_H_

#include <vector>
#include <chrono>
#include <iostream>

#include "Graphics/GraphicView.h"

// Pointer problem
#include "Problems/Pointer/AgentPointer_Emitter.h"
#include "Problems/Pointer/AgentPointer_Receptor.h"

// Drone problem
#include "Problems/Drones/AgentDrones_Hybrid.h"
#include "Bodies/BodyHybrid.h"

// Rocket problem
#include "Problems/Rocket/OneEngine/ProblemRocket_OneEngine.h"
#include "Problems/Rocket/OneEngine/AgentRocket_OneEngine_Emitter.h"
#include "Problems/Rocket/OneEngine/AgentRocket_OneEngine_Receptor.h"

// Rocket problem 2
#include "Problems/Rocket/TwoEngines/ProblemRocket_TwoEngines.h"
#include "Problems/Rocket/TwoEngines/AgentRocket_TwoEngines_Emitter.h"
#include "Problems/Rocket/TwoEngines/AgentRocket_TwoEngines_Receptor.h"


/*
*   The Simulator is the main class of the project.
*   The Simulator is created with an instance of the Problem class. The Problem modelises what it is that the Simulator is trying
*   to solve : drone, pendulum, slink, etc.
*   The Simulator then inits the program, creates the world and the agents, links the agents to their bodies, links the agents
*   to the Problem accordingly.
*
*   It then runs the whole thing via the Run function.
*/

enum AGENT_TYPE
{
	AGENT_EMITTER,
	AGENT_RECEPTOR,
	AGENT_HYBRID
};


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
	int currentAgentType;		// The type set to be placed currently. range from 1 to 9

		// Problem
	//ProblemPointer* problem;   // The instance of the pointer problem.
	//ProblemDrones* problem;   // The instance of the drone problem.
	Problem* problem;   // The instance of the drone problem.

	PROBLEM_TYPE problemType;	// The type of the current problem

	// Helper functions
	void userAddAgent(int x, int y, int agentType);
	void userEraseAgent(Body* body);

	void updateGUIAgentPlacingText();

public:
	Simulator();
	void init();	// Initialise everything. Is called before run()
	void initProblem(PROBLEM_TYPE newProblem);

    // Creates an agent at given position, then add him to the agent list
	Agent* addAgent(float xPos, float yPos, AGENT_TYPE agentType, BODY_TYPE bodyType);

	void checkEvents();					// Check user events
	void run(sf::Time refreshRate);		// Simulation loop

	void clearAgents();

	~Simulator(void);
};

#endif

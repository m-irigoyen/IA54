#include "Simulator.h"


void Simulator::userAddAgent(int x, int y, int agentType)
{
	Agent* newAgent;

	switch (this->problemType)
	{
	case PROBLEM_TYPE::ROCKET_ONE :

		switch (agentType)
		{
		case 0:
			this->addAgent(static_cast<float>(x), static_cast<float>(y), AGENT_TYPE::AGENT_RECEPTOR, BODY_TYPE::BODY_RECEPTOR_MEDIUM);
			break;
		case 1:
			newAgent = this->addAgent(static_cast<float>(x), static_cast<float>(y), AGENT_TYPE::AGENT_EMITTER, BODY_TYPE::BODY_EMITTER);
			((AgentRocket_OneEngine_Emitter*)newAgent)->setAgentType(AGENTTYPE_ROCKET_ONE::ROCKET_ONE_DIRECTION);
			cout << "Placing direction agent" << endl;
			break;
		case 2:
			newAgent = this->addAgent(static_cast<float>(x), static_cast<float>(y), AGENT_TYPE::AGENT_EMITTER, BODY_TYPE::BODY_EMITTER);
			((AgentRocket_OneEngine_Emitter*)newAgent)->setAgentType(AGENTTYPE_ROCKET_ONE::ROCKET_ONE_REGULATOR);
			cout << "Placing regulator agent" << endl;
			break;
		case 3 : 
		newAgent = this->addAgent(static_cast<float>(x), static_cast<float>(y), AGENT_TYPE::AGENT_EMITTER, BODY_TYPE::BODY_EMITTER);
			((AgentRocket_OneEngine_Emitter*)newAgent)->setAgentType(AGENTTYPE_ROCKET_ONE::ROCKET_ONE_STABILIZER);
			cout << "Placing stabilizer agent" << endl;
			break;
		default:
			cout << "ERROR : Simulator::userAddAgent : unexpected agent type" << endl;
		}
		
		break;
	case PROBLEM_TYPE::ROCKET_TWO:
		switch (agentType)
		{
		case 0:
			this->addAgent(static_cast<float>(x), static_cast<float>(y), AGENT_TYPE::AGENT_RECEPTOR, BODY_TYPE::BODY_RECEPTOR_MEDIUM);
			break;
		case 1:
			newAgent = this->addAgent(static_cast<float>(x), static_cast<float>(y), AGENT_TYPE::AGENT_EMITTER, BODY_TYPE::BODY_EMITTER);
			((AgentRocket_TwoEngines_Emitter*)newAgent)->setAgentType(AGENTTYPE_ROCKET_TWO::ROCKET_TWO_DIRECTION);
			cout << "Placing direction agent" << endl;
			break;
		case 2:
			newAgent = this->addAgent(static_cast<float>(x), static_cast<float>(y), AGENT_TYPE::AGENT_EMITTER, BODY_TYPE::BODY_EMITTER);
			((AgentRocket_TwoEngines_Emitter*)newAgent)->setAgentType(AGENTTYPE_ROCKET_TWO::ROCKET_TWO_DESCENT);
			cout << "Placing descent agent" << endl;
			break;
		case 3:
			newAgent = this->addAgent(static_cast<float>(x), static_cast<float>(y), AGENT_TYPE::AGENT_EMITTER, BODY_TYPE::BODY_EMITTER);
			((AgentRocket_TwoEngines_Emitter*)newAgent)->setAgentType(AGENTTYPE_ROCKET_TWO::ROCKET_TWO_STABILIZER_ANGLE);
			cout << "Placing stabilizer angle" << endl;
			break;
		case 4:
			newAgent = this->addAgent(static_cast<float>(x), static_cast<float>(y), AGENT_TYPE::AGENT_EMITTER, BODY_TYPE::BODY_EMITTER);
			((AgentRocket_TwoEngines_Emitter*)newAgent)->setAgentType(AGENTTYPE_ROCKET_TWO::ROCKET_TWO_STABILIZER_HSPEED);
			cout << "Placing stabilizer hSpeed" << endl;
			break;
		case 5:
			newAgent = this->addAgent(static_cast<float>(x), static_cast<float>(y), AGENT_TYPE::AGENT_EMITTER, BODY_TYPE::BODY_EMITTER);
			((AgentRocket_TwoEngines_Emitter*)newAgent)->setAgentType(AGENTTYPE_ROCKET_TWO::ROCKET_TWO_STABILIZER_VSPEED);
			cout << "Placing stabilizer vSpeed" << endl;
			break;
		default:
			cout << "ERROR : Simulator::userAddAgent : unexpected agent type" << endl;
			break;
		}

		break;
	default: 
		cout << "ERROR : cannot place agents in that mode" << endl;
	}
}

void Simulator::userEraseAgent(Body * body)
{
	for (vector<Agent*>::iterator it = this->agents.begin(); it != this->agents.end(); ++it)
	{
		if ((*it)->getBody() == body)
		{
			// Update the problem for the destruction
			switch (this->problemType)
			{
			case PROBLEM_TYPE::ROCKET_ONE:
				if (static_cast<AgentRocket_OneEngine_Emitter*>(*it))
					((ProblemRocket*)this->problem)->setNumberOfEmitters(((ProblemRocket*)this->problem)->getNumberOfEmitters() - 1);
				else
					((ProblemRocket*)this->problem)->setNumberOfReceptors(((ProblemRocket*)this->problem)->getNumberOfReceptors() - 1);
				break;
			case PROBLEM_TYPE::ROCKET_TWO:
				//TODO: implement that when agents are done
				break;
			}

			// Destroy the agent and its body
			this->agents.erase(it);
			this->world.forceEndOfTransmission(static_cast<BodyEmitter*>(body));
			this->world.removeBody(body);
			this->world.updateMaxWaveDistance();	// Updating the max wave distance, in case it changed
			return;
		}
	}
}

void Simulator::updateGUIAgentPlacingText()
{
	switch (this->problemType)
	{
	case PROBLEM_TYPE::ROCKET_ONE :
		switch (this->currentAgentType)
		{
		case 0 :
			this->SFMLView.setCurrentlyPlacingAgent("Receptor");
			break;
		case 1:
			this->SFMLView.setCurrentlyPlacingAgent("Emitter direction");
			break;
		case 2:
			this->SFMLView.setCurrentlyPlacingAgent("Emitter regulator");
			break;
		default:
			this->SFMLView.setCurrentlyPlacingAgent("Emitter stabilizer");
			break;
		}
		break;
	case PROBLEM_TYPE::ROCKET_TWO:
		switch (this->currentAgentType)
		{
		case 0:
			this->SFMLView.setCurrentlyPlacingAgent("Receptor");
			break;
		case 1:
			this->SFMLView.setCurrentlyPlacingAgent("Emitter direction");
			break;
		case 2:
			this->SFMLView.setCurrentlyPlacingAgent("Emitter descent");
			break;
		case 3 : 
			this->SFMLView.setCurrentlyPlacingAgent("Emitter stabilizer_angle");
			break;
		case 4:
			this->SFMLView.setCurrentlyPlacingAgent("Emitter stabilizer_hSpeed");
			break;
		case 5:
			this->SFMLView.setCurrentlyPlacingAgent("Emitter stabilizer_vSpeed");
			break;
		}
		break;
	}
}

Simulator::Simulator() : world(&simulationClock, 800, 600), finishSimulation(false), frameFlag(true), problem(NULL), selectedBody(NULL), problemType(PROBLEM_TYPE::NONE)
{
	init();
}

void Simulator::init()
{
	std::cout << "Initialising" << std::endl;

			// INIT PROBLEM
	// POINTER PROBLEM
	//this->problem = new ProblemPointer(400, 400, secondPointer);

	// Drone Problem
	/*std::map<int, DRONE_BEHAVIOURS> behaviourTable;
	this->problem = new ProblemDrones(behaviourTable, 1);*/

	this->initProblem(PROBLEM_TYPE::ROCKET_ONE);

	std::cout << "Init done" << std::endl;
}

void Simulator::initProblem(PROBLEM_TYPE newProblem)
{
	if (newProblem != this->problemType)
	{
		this->agents.clear();
		this->world.clear();
		if (this->problem != NULL)
		{
			this->problem->clean();
			delete(this->problem);
		}

		this->problemType = newProblem;

		// ROCKET PROBLEM
		if (this->problemType == PROBLEM_TYPE::ROCKET_ONE)
		{
			this->problem = new ProblemRocket_OneEngine();

			// Adding emitters : direction
			AgentRocket_OneEngine_Emitter* newAgent;
			newAgent = static_cast<AgentRocket_OneEngine_Emitter*>(addAgent(200, 200, AGENT_TYPE::AGENT_EMITTER, BODY_TYPE::BODY_EMITTER));
			if (newAgent != NULL)
				newAgent->setAgentType(AGENTTYPE_ROCKET_ONE::ROCKET_ONE_DIRECTION);
			else
				cout << "ERROR : Cast to AgentEmitterRocket* failed" << endl;

			// Adding emitters : regulator
			newAgent = static_cast<AgentRocket_OneEngine_Emitter*>(addAgent(300, 200, AGENT_TYPE::AGENT_EMITTER, BODY_TYPE::BODY_EMITTER));
			if (newAgent != NULL)
				newAgent->setAgentType(AGENTTYPE_ROCKET_ONE::ROCKET_ONE_REGULATOR);
			else
				cout << "ERROR : Cast to AgentEmitterRocket* failed" << endl;

			newAgent = static_cast<AgentRocket_OneEngine_Emitter*>(addAgent(250, 250, AGENT_TYPE::AGENT_EMITTER, BODY_TYPE::BODY_EMITTER));
			if (newAgent != NULL)
				newAgent->setAgentType(AGENTTYPE_ROCKET_ONE::ROCKET_ONE_STABILIZER);
			else
				cout << "ERROR : Cast to AgentEmitterRocket* failed" << endl;

			// Adding stabilizers : precisionLanding
			//TODO:

			// Adding
			addAgent(250, 200, AGENT_TYPE::AGENT_RECEPTOR, BODY_TYPE::BODY_RECEPTOR_MEDIUM);

			((ProblemRocket_OneEngine*)this->problem)->setNumberOfEmitters(2);
			((ProblemRocket_OneEngine*)this->problem)->setNumberOfReceptors(1);
		}
		// ROCKET2 PROBLEM
		else if (this->problemType == PROBLEM_TYPE::ROCKET_TWO)
		{
			this->problem = new ProblemRocket_TwoEngines();

			// Adding
			addAgent(200, 200, AGENT_TYPE::AGENT_RECEPTOR, BODY_TYPE::BODY_RECEPTOR_MEDIUM);

			((ProblemRocket*)this->problem)->setNumberOfEmitters(1);
			((ProblemRocket*)this->problem)->setNumberOfReceptors(1);
		}
		else if (this->problemType == PROBLEM_TYPE::ROCKET_TERRAINEDITOR)
		{
			this->problem = new ProblemRocket_TerrainEditor();
		}

		this->problem->init();

		this->SFMLView.Init(800, 600, this->problem);
		this->SFMLView.setProblemType(this->problemType);
		this->SFMLView.SetWorld(&this->world);
		this->world.setWaveAmplitude(this->problem->getAmplitudeLoss());
		this->window = this->SFMLView.getWindow();
	}
}

Agent * Simulator::addAgent(float xPos, float yPos, AGENT_TYPE agentType, BODY_TYPE bodyType)
{
	Agent* agent = NULL;

	BodyReceptor* receptor = NULL;
	BodyEmitter* emitter = NULL;

	ProblemRocket_OneEngine* castedRocketProblem = static_cast<ProblemRocket_OneEngine*>(this->problem);;
	ProblemRocket_TwoEngines* castedRocket2Problem = static_cast<ProblemRocket_TwoEngines*>(this->problem);

	if (agentType == AGENT_TYPE::AGENT_EMITTER)
	{
		emitter = static_cast<BodyEmitter*>(this->world.createBody(BODY_TYPE::BODY_EMITTER, xPos, yPos));
		if (emitter != NULL)
		{
			switch (this->problemType)
			{
			case PROBLEM_TYPE::ROCKET_ONE:
				if (castedRocketProblem != NULL)
				{
					agent = new AgentRocket_OneEngine_Emitter(castedRocketProblem);
					((AgentRocket_OneEngine_Emitter*)agent)->connectCasted(emitter);
				}
				else
					std::cout << "ERROR : couldn't cast problem to ProblemRocket" << std::endl;
				break;
			case PROBLEM_TYPE::ROCKET_TWO:
				if (castedRocket2Problem != NULL)
				{
					agent = new AgentRocket_TwoEngines_Emitter(castedRocket2Problem);
					((AgentRocket_TwoEngines_Emitter*)agent)->connectCasted(emitter);
				}
				else
					std::cout << "ERROR : couldn't cast problem to ProblemRocket2" << std::endl;
				break;
			}
		}
		else
		{
			std::cout << "ERROR : couldn't cast resulting body" << std::endl;
			return NULL;
		}
	}
	else if (agentType == AGENT_TYPE::AGENT_RECEPTOR)
	{
		if (bodyType == BODY_TYPE::BODY_RECEPTOR_COMPOSITION)
		{
			receptor = static_cast<BodyReceptor_Composition*>(this->world.createBody(BODY_TYPE::BODY_RECEPTOR_COMPOSITION, xPos, yPos));
			if (receptor != NULL)
			{
				switch (this->problemType)
				{
				case PROBLEM_TYPE::ROCKET_ONE:
					if (castedRocketProblem != NULL)
					{
						agent = new AgentRocket_OneEngine_Receptor(castedRocketProblem);
						((AgentRocket_OneEngine_Receptor*)agent)->connectCasted(receptor);
					}
					else
						std::cout << "ERROR : couldn't cast problem to ProblemRocket" << std::endl;
					break;
				case PROBLEM_TYPE::ROCKET_TWO:
					if (castedRocket2Problem != NULL)
					{
						agent = new AgentRocket_TwoEngines_Receptor(castedRocket2Problem);
						((AgentRocket_TwoEngines_Receptor*)agent)->connectCasted(receptor);
					}
					else
						std::cout << "ERROR : couldn't cast problem to ProblemRocket2" << std::endl;
					break;
				}
			}
			else
				std::cout << "ERROR : couldn't cast resulting body" << std::endl;
		}
		else if (bodyType == BODY_TYPE::BODY_RECEPTOR_FULLCOMPOSITION)
		{
			receptor = static_cast<BodyReceptor_CompositionFull*>(this->world.createBody(BODY_TYPE::BODY_RECEPTOR_FULLCOMPOSITION, xPos, yPos));
			if (receptor != NULL)
			{
				switch (this->problemType)
				{
				case PROBLEM_TYPE::ROCKET_ONE:
					if (castedRocketProblem != NULL)
					{
						agent = new AgentRocket_OneEngine_Receptor(castedRocketProblem);
						((AgentRocket_OneEngine_Receptor*)agent)->connectCasted(receptor);
					}
					else
						std::cout << "ERROR : couldn't cast problem to ProblemRocket" << std::endl;
					break;
				case PROBLEM_TYPE::ROCKET_TWO:
					if (castedRocket2Problem != NULL)
					{
						agent = new AgentRocket_TwoEngines_Receptor(castedRocket2Problem);
						((AgentRocket_TwoEngines_Receptor*)agent)->connectCasted(receptor);
					}
					else
						std::cout << "ERROR : couldn't cast problem to ProblemRocket2" << std::endl;
					break;
				}
			}
			else
				std::cout << "ERROR : couldn't cast resulting body" << std::endl;
		}
		else if (bodyType == BODY_TYPE::BODY_RECEPTOR_MEDIUM)
		{
			receptor = static_cast<BodyReceptor_Medium*>(this->world.createBody(BODY_TYPE::BODY_RECEPTOR_MEDIUM, xPos, yPos));
			if (receptor != NULL)
			{
				switch (this->problemType)
				{
				case PROBLEM_TYPE::ROCKET_ONE:
					if (castedRocketProblem != NULL)
					{
						agent = new AgentRocket_OneEngine_Receptor(castedRocketProblem);
						((AgentRocket_OneEngine_Receptor*)agent)->connectCasted(receptor);
					}
					else
						std::cout << "ERROR : couldn't cast problem to ProblemRocket" << std::endl;
					break;
				case PROBLEM_TYPE::ROCKET_TWO:
					if (castedRocket2Problem != NULL)
					{
						agent = new AgentRocket_TwoEngines_Receptor(castedRocket2Problem);
						((AgentRocket_TwoEngines_Receptor*)agent)->connectCasted(receptor);
					}
					else
						std::cout << "ERROR : couldn't cast problem to ProblemRocket2" << std::endl;
					break;
				}
			}
			else
				std::cout << "ERROR : couldn't cast resulting body" << std::endl;
		}
	}

	if (agent != NULL)
		this->agents.push_back(agent);
	return agent;
}

void Simulator::run(sf::Time refreshRate)
{
	simulationClock.restart();

	int eventID = 0;

	sf::Time startTime, endTime, frameTime;

	// VI51 VERSION
	//FIXME : THIS! THIS IS WHY EVERYTHING IS SO FUCKING IMPRECISE! Replace "refreshRate" being send to everything by the ACTUAL FUCKING ELAPSED TIME u_u
	std::cout << "Starting program loop" << std::endl;
	while (!finishSimulation)
	{
		if (this->frameFlag)
		{
			this->frameFlag = false;
			startTime = simulationClock.getElapsedTime();
			//std::cout << endl << "Simulator::Run : STARTING FRAME" << endl;

			// UPDATE STUFF
			// updating problem

			// Old, unprecise version (but at least partially functionnal
			//this->problem->run(refreshRate);
			//this->world.update(refreshRate, startTime);
			this->problem->run(frameTime);
			this->world.update(frameTime, startTime);

			// Updating agents
			for (std::vector<Agent*>::iterator it = this->agents.begin(); it != this->agents.end(); ++it)
			{
				(*it)->live();
			}

			// Drawing
			this->SFMLView.Draw();

			// Ending the frame
			endTime = simulationClock.getElapsedTime();
			frameTime = endTime - startTime;

			/*if (frameTime.asMilliseconds() > 17)
				std::cout << "frame time : " << frameTime.asMilliseconds() << " ms, threshold was " << 1/30 << "ms" << std::endl;*/
			//std::cout << "frame time : " << frameTime.asMilliseconds() << " ms, waiting " << refreshRate.asMilliseconds() - frameTime.asMilliseconds() << " ms" << std::endl;
			//std::cout << "Simulator::Run : FRAME ENDED" << endl;
		}
		else
		{
			checkEvents();	// Checking for user input

			endTime = simulationClock.getElapsedTime();
			frameTime = endTime - startTime;

			if (frameTime > refreshRate)
				frameFlag = true;
		}
	}
}

void Simulator::clearAgents()
{
	for (vector<Agent*>::iterator it = this->agents.begin(); it != this->agents.end(); ++it)
	{
		delete(*it);
	}
	this->agents.clear();
}

Simulator::~Simulator(void)
{
	for (std::vector<Agent*>::iterator it = this->agents.begin(); it != this->agents.end(); ++it)
	{
		delete (*it);
		*it = NULL;
	}
}

// Check simulation events
void Simulator::checkEvents()
{
	// Checking for window events
	sf::Event event;
	while (this->window->pollEvent(event))
	{
        switch (event.type)
        {
				// Close window
                case sf::Event::Closed :
                    this->window->close();
                    finishSimulation = true;
                    break;

				// Key press event
                case sf::Event::KeyPressed :
					switch (event.key.code)
					{
					case sf::Keyboard::F1:
						this->initProblem(PROBLEM_TYPE::ROCKET_TERRAINEDITOR);
						break;

					// Switch problem to Rocket2
					case sf::Keyboard::F2:
						this->initProblem(PROBLEM_TYPE::ROCKET_ONE);
						break;

					// Switch problem to Rocket2
					case sf::Keyboard::F3:
						this->initProblem(PROBLEM_TYPE::ROCKET_TWO);
						break;

					// Quit simulation
					case sf::Keyboard::Escape : 
						this->window->close();
						this->finishSimulation = true;
						break;

					// Toggle wave optimisation
					case sf::Keyboard::O :
						if (this->world.toggleWaveOptimisation())
							std::cout << "Wave optimisation : on" << std::endl;
						else
							std::cout << "Wave optimisation : off" << std::endl;
						break;

					// Toggle wave display
					case sf::Keyboard::W :
						this->SFMLView.toggleDisplayWaves();
						break;

					// Toggle emitter display
					case sf::Keyboard::E:
						this->SFMLView.toggleDisplayEmitters();
						break;

					// Quit receptor display
					case sf::Keyboard::R:
						this->SFMLView.toggleDisplayReceptors();
						break;

					// Toggle simulator display
					case sf::Keyboard::S:
						this->SFMLView.toggleDisplaySimulator();
						break;

					// Agent placement
					case sf::Keyboard::Num0 :
						this->currentAgentType = 0;
						this->updateGUIAgentPlacingText();
						break;
					case sf::Keyboard::Num1:
						this->currentAgentType = 1;
						this->updateGUIAgentPlacingText();
						break;
					case sf::Keyboard::Num2:
						this->currentAgentType = 2;
						this->updateGUIAgentPlacingText();
						break;
					case sf::Keyboard::Num3 :						
						this->currentAgentType = 3;
						this->updateGUIAgentPlacingText();
						break;
					case sf::Keyboard::Num4:
						this->currentAgentType = 4;
						this->updateGUIAgentPlacingText();
						break;
					case sf::Keyboard::Num5:
						this->currentAgentType = 5;
						this->updateGUIAgentPlacingText();
						break;
					case sf::Keyboard::Num6:
						this->currentAgentType = 6;
						this->updateGUIAgentPlacingText();
						break;
					case sf::Keyboard::Num7:
						this->currentAgentType = 7;
						this->updateGUIAgentPlacingText();
						break;
					case sf::Keyboard::Num8:
						this->currentAgentType = 8;
						this->updateGUIAgentPlacingText();
						break;
					case sf::Keyboard::Num9:						
						this->currentAgentType = 9;
						this->updateGUIAgentPlacingText();
						break;

					// Agent suppression
					case sf::Keyboard::Delete :
						if (selectedBody != NULL)
							this->userEraseAgent(selectedBody);
						break;
					}
                    break;

				// Emitter/receptor drag & drop
                case sf::Event::MouseButtonPressed :
					if (event.mouseButton.button == sf::Mouse::Left)
					{
						//std::cout << "Searching body in " <<
						selectedBody = this->world.getClosestBodyFromLocation(
							event.mouseButton.x, event.mouseButton.y, 2 * EMITTER_RADIUSSIZE);
					}
					else if (event.mouseButton.button == sf::Mouse::Right)
					{
						this->userAddAgent(event.mouseButton.x, event.mouseButton.y, this->currentAgentType);
					}
					break;
				// Emitter/receptor drag and drop
                case sf::Event::MouseMoved :
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && selectedBody != NULL)
                    {
                        selectedBody->SetPosition(event.mouseMove.x, event.mouseMove.y);
						this->world.updateMaxWaveDistance();    // Recalculating max wave distance
                        //std::cout << "MOVING BODY TO " << event.mouseMove.x << "," << event.mouseMove.y <<  std::endl;
                    }
                    break;
        }
	}
}

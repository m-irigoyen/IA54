#include "Simulator.h"


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

	this->initProblem(PROBLEM_TYPE::ROCKET2);

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

		if (newProblem == PROBLEM_TYPE::ROCKET)
		{
			this->problem = new ProblemRocket();

			// Adding initial agents
			AgentEmitterRocket* newAgent = static_cast<AgentEmitterRocket*>(addEmitter(200, 200));
			if (newAgent != NULL)
			{
				newAgent->setAgentType(AGENTTYPE_ROCKET::ROCKET_DIRECTION);
			}
			else
			{
				cout << "ERROR : Cast to AgentEmitterRocket* failed" << endl;
			}

			addReceptorComposition(300, 200);

			((ProblemRocket*)this->problem)->setNumberOfEmitters(2);
		}
		else if (newProblem == PROBLEM_TYPE::ROCKET2)
		{
			this->problem = new ProblemRocket2();

			// Adding initial agents
			addEmitter(200, 200);
			addEmitter(200, 400);
			addReceptorComposition(600, 400);
		}

		this->problem->init();

		this->SFMLView.Init(800, 600, this->problem);
		this->SFMLView.setProblemType(this->problemType);
		this->SFMLView.SetWorld(&this->world);
		this->window = this->SFMLView.getWindow();
	}
}

Agent* Simulator::addEmitter(float xPos, float yPos)
{
	Agent* agent;
	BodyEmitter* body = static_cast<BodyEmitter*>(this->world.createBody(BODY_TYPE::EMITTER, xPos, yPos));
	if (body != NULL)
	{
		ProblemRocket* castedRocketProblem;
		ProblemRocket2* castedRocket2Problem;
		switch (this->problemType)
		{
		case PROBLEM_TYPE::ROCKET:
			castedRocketProblem = static_cast<ProblemRocket*>(this->problem);
			if (castedRocketProblem != NULL)
			{
				agent = new AgentEmitterRocket(castedRocketProblem);
				((AgentEmitterRocket*)agent)->connectCasted(body);
				this->agents.push_back(agent);
				
			}
			else
				std::cout << "ERROR : couldn't cast problem to ProblemRocket" << std::endl;
			break;
		case PROBLEM_TYPE::ROCKET2:
			ProblemRocket2* castedRocket2Problem = static_cast<ProblemRocket2*>(this->problem);
			if (castedRocket2Problem != NULL)
			{
				agent = new AgentEmitterRocket2(castedRocket2Problem);
				((AgentEmitterRocket2*)agent)->connectCasted(body);
				this->agents.push_back(agent);
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
	return agent;
}

Agent* Simulator::addReceptorComposition(float xPos, float yPos)
{
	Agent* agent;
	BodyReceptorComposition* body = static_cast<BodyReceptorComposition*>(this->world.createBody(BODY_TYPE::RECEPTOR, xPos, yPos));
	if (body != NULL)
	{
		ProblemRocket* castedRocketProblem;
		ProblemRocket2* castedRocket2Problem;
		switch (this->problemType)
		{
		case PROBLEM_TYPE::ROCKET :
			castedRocketProblem = static_cast<ProblemRocket*>(this->problem);
			if (castedRocketProblem != NULL)
			{
				agent = new AgentReceptorRocket(castedRocketProblem);
				((AgentReceptorRocket*)agent)->connectCasted(body);
				this->agents.push_back(agent);
			}
			else
				std::cout << "ERROR : couldn't cast problem to ProblemRocket" << std::endl;
			break;
		case PROBLEM_TYPE::ROCKET2 :
			castedRocket2Problem = static_cast<ProblemRocket2*>(this->problem);
			if (castedRocket2Problem != NULL)
			{
				agent = new AgentReceptorRocket2(castedRocket2Problem);
				((AgentReceptorRocket2*)agent)->connectCasted(body);
				this->agents.push_back(agent);
			}
			else
				std::cout << "ERROR : couldn't cast problem to ProblemRocket2" << std::endl;
			break;
		}
	}
	else
		std::cout << "ERROR : couldn't cast resulting body" << std::endl;

	return agent;
}

void Simulator::addHybrid(float xPos, float yPos)
{
	/*BodyHybrid* body = static_cast<BodyHybrid*>(this->world.createBody(BODY_TYPE::HYBRID, xPos, yPos));
	if (body != NULL)
	{
		ProblemDrones* castedProblem = static_cast<ProblemDrones*>(this->problem);
		if (castedProblem != NULL)
		{
			AgentHybridProblemDrones* agent = new AgentHybridProblemDrones(castedProblem);
			agent->connectCasted(body);
			this->agents.push_back(agent);
		}
		else
			std::cout << "Simulator::addHybrid : ERROR : couldn't cast problem to ProblemDrones" << std::endl;
	}
	else
		std::cout << "Simulator::addHybrid : ERROR : couldn't cast resulting body" << std::endl;*/
}

void Simulator::run(sf::Time refreshRate)
{
	simulationClock.restart();

	int eventID = 0;

	sf::Time startTime, endTime;

	// VI51 VERSION
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
			this->problem->run(refreshRate);

			this->world.update(refreshRate, startTime);

			// Updating agents
			for (std::vector<Agent*>::iterator it = this->agents.begin(); it != this->agents.end(); ++it)
			{
				(*it)->live();
			}

			// Drawing
			this->SFMLView.Draw();

			// Ending the frame
			endTime = simulationClock.getElapsedTime();
			sf::Time frameTime = endTime - startTime;

			/*if (frameTime.asMilliseconds() > 17)
				std::cout << "frame time : " << frameTime.asMilliseconds() << " ms, threshold was " << 1/30 << "ms" << std::endl;*/
			//std::cout << "frame time : " << frameTime.asMilliseconds() << " ms, waiting " << refreshRate.asMilliseconds() - frameTime.asMilliseconds() << " ms" << std::endl;
			//std::cout << "Simulator::Run : FRAME ENDED" << endl;
		}
		else
		{
			checkEvents();	// Checking for user input

			endTime = simulationClock.getElapsedTime();
			sf::Time frameTime = endTime - startTime;

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
					// Switch problem to Rocket2
					case sf::Keyboard::F1:
						this->initProblem(PROBLEM_TYPE::ROCKET);
						break;

					// Switch problem to Rocket2
					case sf::Keyboard::F2:
						this->initProblem(PROBLEM_TYPE::ROCKET2);
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

					// Toggle problem display
					case sf::Keyboard::P :
						this->SFMLView.toggleDisplayProblem();
						break;

					// Toggle simulator display
					case sf::Keyboard::S:
						this->SFMLView.toggleDisplaySimulator();
						break;
					}
                    break;

				// Emitter/receptor drag & drop
                case sf::Event::MouseButtonPressed :
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        //std::cout << "Searching body in " <<
                        selectedBody = this->world.getClosestBodyFromLocation(
                            event.mouseButton.x,event.mouseButton.y,2*EMITTER_RADIUSSIZE);
                    }
					else if (event.mouseButton.button == sf::Mouse::Right)
                        this->addEmitter(event.mouseButton.x,event.mouseButton.y);
                    else if (event.mouseButton.button == sf::Mouse::Middle)
                        this->addReceptorComposition(event.mouseButton.x,event.mouseButton.y);
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

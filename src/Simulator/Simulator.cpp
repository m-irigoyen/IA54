#include "Simulator.h"

void Simulator::userAddAgent(int x, int y, int agentType)
{
	Agent* newAgent;

	switch (this->problemType)
	{
	case PROBLEM_TYPE::ROCKET_ONE :
		switch ((AGENTTYPE_ROCKET_ONE)agentType)
		{
		case AGENTTYPE_ROCKET_ONE::ROCKET_ONE_RECEPTOR :
			this->addAgent(static_cast<float>(x), static_cast<float>(y), AGENT_TYPE::AGENT_RECEPTOR, BODY_TYPE::BODY_RECEPTOR_MEDIUM);
			((ProblemRocket*)this->problem)->addedAgent(agentType);
			//cout << "Placing RocketOne receptor agent" << endl;
			break;
		case AGENTTYPE_ROCKET_ONE::ROCKET_ONE_DIRECTION:
			newAgent = this->addAgent(static_cast<float>(x), static_cast<float>(y), AGENT_TYPE::AGENT_EMITTER, BODY_TYPE::BODY_EMITTER);
			((AgentRocket_OneEngine_Emitter*)newAgent)->setType(AGENTTYPE_ROCKET_ONE::ROCKET_ONE_DIRECTION);
			((ProblemRocket*)this->problem)->addedAgent(agentType);
			//cout << "Placing RocketOne direction agent" << endl;
			break;
		case AGENTTYPE_ROCKET_ONE::ROCKET_ONE_ALTITUDE:
			newAgent = this->addAgent(static_cast<float>(x), static_cast<float>(y), AGENT_TYPE::AGENT_EMITTER, BODY_TYPE::BODY_EMITTER);
			((AgentRocket_OneEngine_Emitter*)newAgent)->setType((int)AGENTTYPE_ROCKET_ONE::ROCKET_ONE_ALTITUDE);
			((ProblemRocket*)this->problem)->addedAgent(agentType);
			//cout << "Placing RocketOne altitude agent" << endl;
			break;
		case AGENTTYPE_ROCKET_ONE::ROCKET_ONE_AVOIDER:
			newAgent = this->addAgent(static_cast<float>(x), static_cast<float>(y), AGENT_TYPE::AGENT_EMITTER, BODY_TYPE::BODY_EMITTER);
			((AgentRocket_OneEngine_Emitter*)newAgent)->setType((int)AGENTTYPE_ROCKET_ONE::ROCKET_ONE_AVOIDER);
			((ProblemRocket*)this->problem)->addedAgent(agentType);
			break;
		case AGENTTYPE_ROCKET_ONE::ROCKET_ONE_STABILIZER_HSPEED:
			newAgent = this->addAgent(static_cast<float>(x), static_cast<float>(y), AGENT_TYPE::AGENT_EMITTER, BODY_TYPE::BODY_EMITTER);
			((AgentRocket_OneEngine_Emitter*)newAgent)->setType((int)AGENTTYPE_ROCKET_ONE::ROCKET_ONE_STABILIZER_HSPEED);
			((ProblemRocket*)this->problem)->addedAgent(agentType);
			//cout << "Placing RocketOne stabilizer_hSpeed agent" << endl;
			break;
		case AGENTTYPE_ROCKET_ONE::ROCKET_ONE_STABILIZER_VSPEED:
			newAgent = this->addAgent(static_cast<float>(x), static_cast<float>(y), AGENT_TYPE::AGENT_EMITTER, BODY_TYPE::BODY_EMITTER);
			((AgentRocket_OneEngine_Emitter*)newAgent)->setType((int)AGENTTYPE_ROCKET_ONE::ROCKET_ONE_STABILIZER_VSPEED);
			((ProblemRocket*)this->problem)->addedAgent(agentType);
			//cout << "Placing RocketOne stabilizer_vSpeed agent" << endl;
			break;
		default:
			cout << "ERROR : Simulator::userAddAgent : unexpected agent type" << endl;
		}
		
		break;
	case PROBLEM_TYPE::ROCKET_TWO:
		switch ((AGENTTYPE_ROCKET_TWO)agentType)
		{
		case AGENTTYPE_ROCKET_TWO::ROCKET_TWO_RECEPTOR:
			this->addAgent(static_cast<float>(x), static_cast<float>(y), AGENT_TYPE::AGENT_RECEPTOR, BODY_TYPE::BODY_RECEPTOR_MEDIUM);
			((ProblemRocket*)this->problem)->addedAgent(agentType);
			//cout << "Placing RocketTwo receptor agent" << endl;
			break;
		case AGENTTYPE_ROCKET_TWO::ROCKET_TWO_DIRECTION:
			newAgent = this->addAgent(static_cast<float>(x), static_cast<float>(y), AGENT_TYPE::AGENT_EMITTER, BODY_TYPE::BODY_EMITTER);
			((AgentRocket_TwoEngines_Emitter*)newAgent)->setType((int)AGENTTYPE_ROCKET_TWO::ROCKET_TWO_DIRECTION);
			((ProblemRocket*)this->problem)->addedAgent(agentType);
			//cout << "Placing direction agent" << endl;
			break;
		case AGENTTYPE_ROCKET_TWO::ROCKET_TWO_ALTITUDE:
			newAgent = this->addAgent(static_cast<float>(x), static_cast<float>(y), AGENT_TYPE::AGENT_EMITTER, BODY_TYPE::BODY_EMITTER);
			((AgentRocket_TwoEngines_Emitter*)newAgent)->setType((int)AGENTTYPE_ROCKET_TWO::ROCKET_TWO_ALTITUDE);
			((ProblemRocket*)this->problem)->addedAgent(agentType);
			//cout << "Placing altitude agent" << endl;
			break;
		case AGENTTYPE_ROCKET_TWO::ROCKET_TWO_AVOIDER:
			newAgent = this->addAgent(static_cast<float>(x), static_cast<float>(y), AGENT_TYPE::AGENT_EMITTER, BODY_TYPE::BODY_EMITTER);
			((AgentRocket_TwoEngines_Emitter*)newAgent)->setType((int)AGENTTYPE_ROCKET_TWO::ROCKET_TWO_AVOIDER);
			((ProblemRocket*)this->problem)->addedAgent(agentType);
			//cout << "Placing altitude agent" << endl;
			break;
		case AGENTTYPE_ROCKET_TWO::ROCKET_TWO_STABILIZER_ANGLE:
			newAgent = this->addAgent(static_cast<float>(x), static_cast<float>(y), AGENT_TYPE::AGENT_EMITTER, BODY_TYPE::BODY_EMITTER);
			((AgentRocket_TwoEngines_Emitter*)newAgent)->setType((int)AGENTTYPE_ROCKET_TWO::ROCKET_TWO_STABILIZER_ANGLE);
			((ProblemRocket*)this->problem)->addedAgent(agentType);
			//cout << "Placing stabilizer angle" << endl;
			break;
		case AGENTTYPE_ROCKET_TWO::ROCKET_TWO_STABILIZER_HSPEED:
			newAgent = this->addAgent(static_cast<float>(x), static_cast<float>(y), AGENT_TYPE::AGENT_EMITTER, BODY_TYPE::BODY_EMITTER);
			((AgentRocket_TwoEngines_Emitter*)newAgent)->setType((int)AGENTTYPE_ROCKET_TWO::ROCKET_TWO_STABILIZER_HSPEED);
			((ProblemRocket*)this->problem)->addedAgent(agentType);
			//cout << "Placing stabilizer hSpeed" << endl;
			break;
		case AGENTTYPE_ROCKET_TWO::ROCKET_TWO_STABILIZER_VSPEED:
			newAgent = this->addAgent(static_cast<float>(x), static_cast<float>(y), AGENT_TYPE::AGENT_EMITTER, BODY_TYPE::BODY_EMITTER);
			((AgentRocket_TwoEngines_Emitter*)newAgent)->setType((int)AGENTTYPE_ROCKET_TWO::ROCKET_TWO_STABILIZER_VSPEED);
			((ProblemRocket*)this->problem)->addedAgent(agentType);
			//cout << "Placing stabilizer vSpeed" << endl;
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
			this->removeAgent(it);
			return;
		}
	}
}

void Simulator::updateGUIAgentPlacingText()
{
	switch (this->problemType)
	{
	case PROBLEM_TYPE::ROCKET_ONE :
		switch ((AGENTTYPE_ROCKET_ONE)this->currentAgentType)
		{
		case AGENTTYPE_ROCKET_ONE::ROCKET_ONE_RECEPTOR:
			this->SFMLView.setCurrentlyPlacingAgent("Receptor", currentAgentType);
			break;
		case AGENTTYPE_ROCKET_ONE::ROCKET_ONE_DIRECTION:
			this->SFMLView.setCurrentlyPlacingAgent("Emitter direction", currentAgentType);
			break;
		case AGENTTYPE_ROCKET_ONE::ROCKET_ONE_ALTITUDE:
			this->SFMLView.setCurrentlyPlacingAgent("Emitter altitude", currentAgentType);
			break;
		case AGENTTYPE_ROCKET_ONE::ROCKET_ONE_AVOIDER:
			this->SFMLView.setCurrentlyPlacingAgent("Emitter avoider", currentAgentType);
			break;
		case AGENTTYPE_ROCKET_ONE::ROCKET_ONE_STABILIZER_HSPEED:
			this->SFMLView.setCurrentlyPlacingAgent("Emitter stabilizer_hSpeed", currentAgentType);
			break;
		case AGENTTYPE_ROCKET_ONE::ROCKET_ONE_STABILIZER_VSPEED:
			this->SFMLView.setCurrentlyPlacingAgent("Emitter stabilizer_vSpeed", currentAgentType);
			break;
		default :
			this->SFMLView.setCurrentlyPlacingAgent("", 0);
			break;
		}
		break;
	case PROBLEM_TYPE::ROCKET_TWO:
		switch ((AGENTTYPE_ROCKET_TWO)this->currentAgentType)
		{
		case AGENTTYPE_ROCKET_TWO::ROCKET_TWO_RECEPTOR:
			this->SFMLView.setCurrentlyPlacingAgent("Receptor", currentAgentType);
			break;
		case AGENTTYPE_ROCKET_TWO::ROCKET_TWO_DIRECTION:
			this->SFMLView.setCurrentlyPlacingAgent("Emitter direction", currentAgentType);
			break;
		case AGENTTYPE_ROCKET_TWO::ROCKET_TWO_ALTITUDE:
			this->SFMLView.setCurrentlyPlacingAgent("Emitter descent", currentAgentType);
			break;
		case AGENTTYPE_ROCKET_TWO::ROCKET_TWO_AVOIDER:
			this->SFMLView.setCurrentlyPlacingAgent("Emitter avoider", currentAgentType);
			break;
		case AGENTTYPE_ROCKET_TWO::ROCKET_TWO_STABILIZER_ANGLE:
			this->SFMLView.setCurrentlyPlacingAgent("Emitter stabilizer_angle", currentAgentType);
			break;
		case AGENTTYPE_ROCKET_TWO::ROCKET_TWO_STABILIZER_HSPEED:
			this->SFMLView.setCurrentlyPlacingAgent("Emitter stabilizer_hSpeed", currentAgentType);
			break;
		case AGENTTYPE_ROCKET_TWO::ROCKET_TWO_STABILIZER_VSPEED:
			this->SFMLView.setCurrentlyPlacingAgent("Emitter stabilizer_vSpeed", currentAgentType);
			break;
		default:
			this->SFMLView.setCurrentlyPlacingAgent("", 0);
			break;
		}
		break;
	}
}

void Simulator::updateBrain(float elapsedTime)
{
	this->rocketBrain->live();
	map<int, int> desiredState = this->rocketBrain->getDesiredState();
	map<int, int>& agentCount = ((ProblemRocket*)this->problem)->getAgentCount();

	for (pair<int, int> p : desiredState)
	{
		// Desired number is different
		if (agentCount.at(p.first) != p.second)
		{
			this->regulateAgentNumber(p.first, p.second);
		}
	}
}

void Simulator::regulateAgentNumber(int agentType, int desiredNumber)
{
	if (this->problemType != PROBLEM_TYPE::ROCKET_ONE
		&& this->problemType != PROBLEM_TYPE::ROCKET_TWO)
		return;

	map<int, int>& agentCount = ((ProblemRocket*)this->problem)->getAgentCount();

	if (desiredNumber > agentCount.at(agentType))
	{
		// Adding agents, the easy part
		int offset = 0;
		while (desiredNumber > agentCount.at(agentType))
		{
			// Adding a slight offset to avoid the case where agents are on top of each other
			Vector v;
			v.randomize();
			//this->getRandomPos(agentType, x, y);
			this->userAddAgent(200 + v.getX() * 40,
				200 + v.getY() * 40,
				agentType);
			++offset;
		}
	}
	else if (desiredNumber < agentCount.at(agentType))
	{
		// Removing agents : the hard part
		if (this->agents.size() > 0)
		{
			for (vector<Agent*>::iterator it = this->agents.begin(); it != this->agents.end(); ++it)
			{
				if ((*it)->getType() == agentType)
				{
					it = this->removeAgent(it);

					if (agentCount.at(agentType) == desiredNumber || it == this->agents.end())
						break;
				}
			}
		}
	}
}

void Simulator::getRandomPos(int agentType, float & x, float & y)
{
	//TODO: implement that if enough time
}

void Simulator::resetAgentPositions()
{
	/*this->userAddAgent(200 + v.getX() * 40,
		200 + v.getY() * 40,*/

	for (Agent* a : this->agents)
	{
		// IF the agent isn't a receptor
		if (a->getType() != 0)
		{
			Vector v;
			v.randomize();
			a->getBody()->SetPosition(200 + v.getX() * 40,
				200 + v.getY() * 40);
		}
	}
	this->world.clearWaves();
}

vector<Agent*>::iterator Simulator::removeAgent(Agent * agent)
{
	for (vector<Agent*>::iterator it = this->agents.begin(); it != this->agents.end(); ++it)
	{
		if (*it == agent)
			return this->removeAgent(it);
	}
	return this->agents.end();
}

vector<Agent*>::iterator Simulator::removeAgent(vector<Agent*>::iterator agent)
{
	if (this->problemType == PROBLEM_TYPE::ROCKET_ONE
		|| this->problemType == PROBLEM_TYPE::ROCKET_TWO)
		((ProblemRocket*)this->problem)->removedAgent((*agent)->getType());

	// Destroy the agent and its body
	if ((*agent)->getBody() != NULL)
	{
		this->world.forceEndOfTransmission(static_cast<BodyEmitter*>((*agent)->getBody()));
		this->world.removeBody((*agent)->getBody());
		this->world.updateMaxWaveDistance();	// Updating the max wave distance, in case it changed
	}
	return this->agents.erase(agent);;
}

Simulator::Simulator() : world(&simulationClock, 800, 600), finishSimulation(false), frameFlag(true), problem(NULL), selectedBody(NULL), problemType(PROBLEM_TYPE::NONE), rocketBrain(NULL)
{
	init();
}

void Simulator::init()
{
	std::cout << "Initialising" << std::endl;

	srand(time(NULL));
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
			this->problem = NULL;

			if (this->rocketBrain != NULL)
			{
				delete(this->rocketBrain);
				this->rocketBrain = NULL;
			}
		}

		this->problemType = newProblem;

		// ROCKET PROBLEM
		if (this->problemType == PROBLEM_TYPE::ROCKET_ONE)
		{
			this->problem = new ProblemRocket_OneEngine();

			//Creating brain
			this->rocketBrain = new AgentRocket_OneEngine_Brain(static_cast<ProblemRocket_OneEngine*>(this->problem));

			// Adding emitters : direction
			AgentRocket_OneEngine_Emitter* newAgent;
			newAgent = static_cast<AgentRocket_OneEngine_Emitter*>(addAgent(180, 200, AGENT_TYPE::AGENT_EMITTER, BODY_TYPE::BODY_EMITTER));
			if (newAgent != NULL)
			{
				newAgent->setType((int)AGENTTYPE_ROCKET_ONE::ROCKET_ONE_DIRECTION);
				((ProblemRocket*)this->problem)->addedAgent(AGENTTYPE_ROCKET_ONE::ROCKET_ONE_DIRECTION);
			}
				

			// Adding emitters : regulator
			newAgent = static_cast<AgentRocket_OneEngine_Emitter*>(addAgent(220, 200, AGENT_TYPE::AGENT_EMITTER, BODY_TYPE::BODY_EMITTER));
			if (newAgent != NULL)
			{
				newAgent->setType((int)AGENTTYPE_ROCKET_ONE::ROCKET_ONE_ALTITUDE);
				((ProblemRocket*)this->problem)->addedAgent(AGENTTYPE_ROCKET_ONE::ROCKET_ONE_ALTITUDE);
			}

			newAgent = static_cast<AgentRocket_OneEngine_Emitter*>(addAgent(200, 180, AGENT_TYPE::AGENT_EMITTER, BODY_TYPE::BODY_EMITTER));
			if (newAgent != NULL)
			{
				newAgent->setType((int)AGENTTYPE_ROCKET_ONE::ROCKET_ONE_STABILIZER_HSPEED);
				((ProblemRocket*)this->problem)->addedAgent(AGENTTYPE_ROCKET_ONE::ROCKET_ONE_STABILIZER_HSPEED);
			}
			
			newAgent = static_cast<AgentRocket_OneEngine_Emitter*>(addAgent(200, 220, AGENT_TYPE::AGENT_EMITTER, BODY_TYPE::BODY_EMITTER));
			if (newAgent != NULL)
			{
				newAgent->setType((int)AGENTTYPE_ROCKET_ONE::ROCKET_ONE_STABILIZER_VSPEED);
				((ProblemRocket*)this->problem)->addedAgent(AGENTTYPE_ROCKET_ONE::ROCKET_ONE_STABILIZER_VSPEED);
			}

			// Adding receptor
			addAgent(200, 200, AGENT_TYPE::AGENT_RECEPTOR, BODY_TYPE::BODY_RECEPTOR_MEDIUM)->setType((int)AGENTTYPE_ROCKET_ONE::ROCKET_ONE_RECEPTOR);
			((ProblemRocket*)this->problem)->addedAgent(AGENTTYPE_ROCKET_ONE::ROCKET_ONE_RECEPTOR);

		}
		// ROCKET2 PROBLEM
		else if (this->problemType == PROBLEM_TYPE::ROCKET_TWO)
		{
			this->problem = new ProblemRocket_TwoEngines();

			//Creating brain
			this->rocketBrain = new AgentRocket_TwoEngines_Brain(static_cast<ProblemRocket_TwoEngines*>(this->problem));

			//Emitters
			// Direction
			AgentRocket_TwoEngines_Emitter* newAgent;
			newAgent = static_cast<AgentRocket_TwoEngines_Emitter*>(addAgent(170, 200, AGENT_TYPE::AGENT_EMITTER, BODY_TYPE::BODY_EMITTER));
			if (newAgent != NULL)
			{
				newAgent->setType((int)AGENTTYPE_ROCKET_TWO::ROCKET_TWO_DIRECTION);
				((ProblemRocket*)this->problem)->addedAgent(AGENTTYPE_ROCKET_TWO::ROCKET_TWO_DIRECTION);
			}

			// Altitude
			newAgent = static_cast<AgentRocket_TwoEngines_Emitter*>(addAgent(220, 220, AGENT_TYPE::AGENT_EMITTER, BODY_TYPE::BODY_EMITTER));
			if (newAgent != NULL)
			{
				newAgent->setType((int)AGENTTYPE_ROCKET_TWO::ROCKET_TWO_ALTITUDE);
				((ProblemRocket*)this->problem)->addedAgent(AGENTTYPE_ROCKET_TWO::ROCKET_TWO_ALTITUDE);
			}

			// Stabilizer Angle
			newAgent = static_cast<AgentRocket_TwoEngines_Emitter*>(addAgent(230, 200, AGENT_TYPE::AGENT_EMITTER, BODY_TYPE::BODY_EMITTER));
			if (newAgent != NULL)
			{
				newAgent->setType((int)AGENTTYPE_ROCKET_TWO::ROCKET_TWO_STABILIZER_ANGLE);
				((ProblemRocket*)this->problem)->addedAgent(AGENTTYPE_ROCKET_TWO::ROCKET_TWO_STABILIZER_ANGLE);
			}

			// Stabilizer hSpeed
			newAgent = static_cast<AgentRocket_TwoEngines_Emitter*>(addAgent(200, 170, AGENT_TYPE::AGENT_EMITTER, BODY_TYPE::BODY_EMITTER));
			if (newAgent != NULL)
			{
				newAgent->setType((int)AGENTTYPE_ROCKET_TWO::ROCKET_TWO_STABILIZER_HSPEED);
				((ProblemRocket*)this->problem)->addedAgent(AGENTTYPE_ROCKET_TWO::ROCKET_TWO_STABILIZER_HSPEED);
			}

			// Stabilizer vSpeed
			newAgent = static_cast<AgentRocket_TwoEngines_Emitter*>(addAgent(200, 230, AGENT_TYPE::AGENT_EMITTER, BODY_TYPE::BODY_EMITTER));
			if (newAgent != NULL)
			{
				newAgent->setType((int)AGENTTYPE_ROCKET_TWO::ROCKET_TWO_STABILIZER_VSPEED);
				((ProblemRocket*)this->problem)->addedAgent(AGENTTYPE_ROCKET_TWO::ROCKET_TWO_STABILIZER_VSPEED);
			}

			// Receptor
			addAgent(200, 200, AGENT_TYPE::AGENT_RECEPTOR, BODY_TYPE::BODY_RECEPTOR_MEDIUM)->setType((int)AGENTTYPE_ROCKET_TWO::ROCKET_TWO_RECEPTOR);
			((ProblemRocket*)this->problem)->addedAgent(AGENTTYPE_ROCKET_TWO::ROCKET_TWO_RECEPTOR);

		}
		else if (this->problemType == PROBLEM_TYPE::ROCKET_TERRAINEDITOR)
		{
			this->problem = new ProblemRocket_TerrainEditor();
		}

		this->problem->init();

		this->SFMLView.Init(400, 400, 1024, 768, this->problem);
		this->SFMLView.setProblemType(this->problemType);
		this->SFMLView.SetWorld(&this->world);
		this->world.setWaveAmplitude(this->problem->getAmplitudeLoss());
		this->window = this->SFMLView.getWindow();

		//FIXME : find a more elegant solution to that stupid brain gui
		if (this->rocketBrain != NULL)
			this->SFMLView.setBrainActive(this->rocketBrain->isActive());
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
				{
					std::cout << "ERROR : couldn't cast problem to ProblemRocket" << std::endl;
				}
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
			// Brain first
			if (this->rocketBrain != NULL && this->rocketBrain->isActive())
				this->updateBrain(frameTime.asSeconds());

			// Then regular agents
			for (std::vector<Agent*>::iterator it = this->agents.begin(); it != this->agents.end(); ++it)
			{
				(*it)->live();
			}

			// Drawing
			this->SFMLView.Draw();

			if (this->problem->getResetAgent())
				this->resetAgentPositions();

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
						this->SFMLView.resetText();
						this->initProblem(PROBLEM_TYPE::ROCKET_TERRAINEDITOR);
						break;

					// Switch problem to Rocket2
					case sf::Keyboard::F2:
						this->SFMLView.resetText();
						this->initProblem(PROBLEM_TYPE::ROCKET_ONE);
						break;

					// Switch problem to Rocket2
					case sf::Keyboard::F3:
						this->SFMLView.resetText();
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

					case sf::Keyboard::Add :
						this->world.setWaveSpeed(this->world.getWaveSpeed() + 1);
						break;

					case sf::Keyboard::Subtract:
						this->world.setWaveSpeed(this->world.getWaveSpeed() - 1);
						break;

					// Quit receptor display
					case sf::Keyboard::R:
						this->resetAgentPositions();
						break;

					// toggling brain 
					case sf::Keyboard::B :
						if (this->rocketBrain != NULL)
						{
							this->rocketBrain->toggleActive();
							this->SFMLView.setBrainActive(this->rocketBrain->isActive());
						}
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

				case sf::Event::Resized :
					this->window->setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
					break;
        }
	}
}

#include "Problems/Rocket/TwoEngines/AgentRocket_TwoEngines_Receptor.h"

AgentRocket_TwoEngines_Receptor::AgentRocket_TwoEngines_Receptor(ProblemRocket_TwoEngines * problem, BodyReceptor_Composition * body, AGENTTYPE_ROCKET_TWO type) : AgentReceptor(problem,body), castedProblem(problem), agentType(type)
{
}

void AgentRocket_TwoEngines_Receptor::live()
{
	// Getting perception from body
	WAVE perception = this->castedBody->getPerception();

	switch (agentType)
	{
	case AGENTTYPE_ROCKET_TWO::ROCKET_TWO_DIRECTION:
		
		break;
	}
}

bool AgentRocket_TwoEngines_Receptor::isLinked()
{
	return AgentReceptor::isLinked();
}

bool AgentRocket_TwoEngines_Receptor::isProblemLinked()
{
	return this->castedProblem != NULL;
}

void AgentRocket_TwoEngines_Receptor::setAgentType(AGENTTYPE_ROCKET_TWO type)
{
	this->agentType = type;
}

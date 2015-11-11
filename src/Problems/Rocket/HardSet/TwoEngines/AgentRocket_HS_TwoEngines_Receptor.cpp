#include "Problems/Rocket/HardSet/TwoEngines/AgentRocket_HS_TwoEngines_Receptor.h"

AgentRocket_HS_TwoEngines_Receptor::AgentRocket_HS_TwoEngines_Receptor(ProblemRocket_HS_TwoEngines * problem, BodyReceptor_Composition * body, AGENTTYPE_ROCKET_HS_TWO type) : AgentReceptor(problem,body), castedProblem(problem), agentType(type)
{
}

void AgentRocket_HS_TwoEngines_Receptor::live()
{
	// Getting perception from body
	WAVE_COMPOSITION perception = this->castedBody->getPerception();

	switch (agentType)
	{
	case AGENTTYPE_ROCKET_HS_TWO::ROCKET_HS_TWO_DIRECTION:
		
		//this->castedBody->
		break;
	}
}

bool AgentRocket_HS_TwoEngines_Receptor::isLinked()
{
	return AgentReceptor::isLinked();
}

bool AgentRocket_HS_TwoEngines_Receptor::isProblemLinked()
{
	return this->castedProblem != NULL;
}

void AgentRocket_HS_TwoEngines_Receptor::setAgentType(AGENTTYPE_ROCKET_HS_TWO type)
{
	this->agentType = type;
}

#include "Problems/Rocket/HardSet/TwoEngines/AgentRocket_HS_TwoEngines_Emitter.h"

AgentRocket_HS_TwoEngines_Emitter::AgentRocket_HS_TwoEngines_Emitter(ProblemRocket_HS_TwoEngines * problem, BodyEmitter * body, AGENTTYPE_ROCKET_HS_TWO type) : AgentEmitter(problem,body), castedProblem(problem), agentType(type)
{
}

void AgentRocket_HS_TwoEngines_Emitter::live()
{
	switch (this->agentType)
	{
	case AGENTTYPE_ROCKET_HS_TWO::ROCKET_HS_TWO_DIRECTION :
		this->castedBody->send(10, 100);
		break;
	case AGENTTYPE_ROCKET_HS_TWO::ROCKET_HS_TWO_POWER:
		this->castedBody->send(10, 100);
		break;
	}
}

bool AgentRocket_HS_TwoEngines_Emitter::isLinked()
{
	return AgentEmitter::isLinked();
}

bool AgentRocket_HS_TwoEngines_Emitter::isProblemLinked()
{
	return this->castedProblem != NULL;
}

void AgentRocket_HS_TwoEngines_Emitter::setAgentType(AGENTTYPE_ROCKET_HS_TWO type)
{
	this->agentType = type;
}

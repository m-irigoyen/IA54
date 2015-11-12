#include "Problems/Rocket/TwoEngines/AgentRocket_TwoEngines_Emitter.h"

AgentRocket_TwoEngines_Emitter::AgentRocket_TwoEngines_Emitter(ProblemRocket_TwoEngines * problem, BodyEmitter * body, AGENTTYPE_ROCKET_TWO type) : AgentEmitter(problem,body), castedProblem(problem), agentType(type)
{
}

void AgentRocket_TwoEngines_Emitter::live()
{
	switch (this->agentType)
	{
	case AGENTTYPE_ROCKET_TWO::ROCKET_TWO_DIRECTION :
		this->castedBody->send(10, 100);
		break;
	case AGENTTYPE_ROCKET_TWO::ROCKET_TWO_POWER:
		this->castedBody->send(10, 100);
		break;
	}
}

bool AgentRocket_TwoEngines_Emitter::isLinked()
{
	return AgentEmitter::isLinked();
}

bool AgentRocket_TwoEngines_Emitter::isProblemLinked()
{
	return this->castedProblem != NULL;
}

void AgentRocket_TwoEngines_Emitter::setAgentType(AGENTTYPE_ROCKET_TWO type)
{
	this->agentType = type;
}

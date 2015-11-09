#include "AgentEmitterRocket2.h"

AgentEmitterRocket2::AgentEmitterRocket2(ProblemRocket2 * problem, BodyEmitter * body, AGENTTYPE_ROCKET2 type) : AgentEmitter(problem,body), castedProblem(problem), agentType(type)
{
}

void AgentEmitterRocket2::live()
{
	switch (this->agentType)
	{
	case AGENTTYPE_ROCKET2::ROCKET2_DIRECTION :
		this->castedBody->send(10, 100);
		break;
	case AGENTTYPE_ROCKET2::ROCKET2_POWER:
		this->castedBody->send(10, 100);
		break;
	}
}

bool AgentEmitterRocket2::isLinked()
{
	return AgentEmitter::isLinked();
}

bool AgentEmitterRocket2::isProblemLinked()
{
	return this->castedProblem != NULL;
}

void AgentEmitterRocket2::setAgentType(AGENTTYPE_ROCKET2 type)
{
	this->agentType = type;
}

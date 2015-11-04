#include "AgentEmitterRocket.h"

AgentEmitterRocket::AgentEmitterRocket(ProblemRocket * problem, BodyEmitter * body, AGENTTYPE_ROCKET type) : AgentEmitter(problem,body), castedProblem(problem), agentType(type)
{
}

void AgentEmitterRocket::live()
{
	switch (this->agentType)
	{
	case AGENTTYPE_ROCKET::ROCKET_DIRECTION :
		this->castedBody->send(10, 100);
		break;
	case AGENTTYPE_ROCKET::ROCKET_POWER:
		this->castedBody->send(10, 100);
		break;
	}
}

bool AgentEmitterRocket::isLinked()
{
	return AgentEmitter::isLinked();
}

bool AgentEmitterRocket::isProblemLinked()
{
	return this->castedProblem != NULL;
}

void AgentEmitterRocket::setAgentType(AGENTTYPE_ROCKET type)
{
	this->agentType = type;
}

#include "Agents/AgentReceptorRocket.h"

AgentReceptorRocket::AgentReceptorRocket(ProblemRocket * problem, BodyReceptorComposition * body, AGENTTYPE_ROCKET type) : AgentReceptor(problem,body), castedProblem(problem), agentType(type)
{
}

void AgentReceptorRocket::live()
{
	// Getting perception from body
	WAVE_COMPOSITION perception = this->castedBody->getPerception();

	
}

bool AgentReceptorRocket::isLinked()
{
	return AgentReceptor::isLinked();
}

bool AgentReceptorRocket::isProblemLinked()
{
	return this->castedProblem != NULL;
}

void AgentReceptorRocket::setAgentType(AGENTTYPE_ROCKET type)
{
	this->agentType = type;
}

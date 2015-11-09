#include "Agents/AgentReceptorRocket2.h"

AgentReceptorRocket2::AgentReceptorRocket2(ProblemRocket2 * problem, BodyReceptorComposition * body, AGENTTYPE_ROCKET2 type) : AgentReceptor(problem,body), castedProblem(problem), agentType(type)
{
}

void AgentReceptorRocket2::live()
{
	// Getting perception from body
	WAVE_COMPOSITION perception = this->castedBody->getPerception();

	switch (agentType)
	{
	case AGENTTYPE_ROCKET2::ROCKET2_DIRECTION:
		
		//this->castedBody->
		break;
	}
}

bool AgentReceptorRocket2::isLinked()
{
	return AgentReceptor::isLinked();
}

bool AgentReceptorRocket2::isProblemLinked()
{
	return this->castedProblem != NULL;
}

void AgentReceptorRocket2::setAgentType(AGENTTYPE_ROCKET2 type)
{
	this->agentType = type;
}

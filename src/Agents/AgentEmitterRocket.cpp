#include "AgentEmitterRocket.h"

AgentEmitterRocket::AgentEmitterRocket(ProblemRocket * problem, BodyEmitter * body) : AgentEmitter(problem,body), castedProblem(problem)
{
}

void AgentEmitterRocket::live()
{
	this->castedBody->send(10, 100);
}

bool AgentEmitterRocket::isLinked()
{
	return AgentEmitter::isLinked();
}

bool AgentEmitterRocket::isProblemLinked()
{
	return this->castedProblem != NULL;
}

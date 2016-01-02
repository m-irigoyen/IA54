#include "Agents/AgentReceptor.h"

AgentReceptor::AgentReceptor(Problem* problem, BodyReceptor* body, int type) : Agent(problem, body, type)
{
	connectCasted(body);
}

void AgentReceptor::live()
{
}


void AgentReceptor::connectCasted(BodyReceptor* body)
{
	if (body != NULL)
	{
		Agent::connect(body);
		this->castedBody = body;
	}
}

void AgentReceptor::disconnect()
{
	Agent::disconnect();
	this->castedBody = NULL;
}

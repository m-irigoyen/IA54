#include "Agents/AgentHybrid.h"

AgentHybrid::AgentHybrid(Problem * problem, BodyHybrid * body) : Agent(problem, body)
{
}

void AgentHybrid::connectCasted(BodyHybrid * body)
{
	if (body != NULL)
	{
		Agent::connect(body);
		this->castedBody = body;
	}
}

void AgentHybrid::disconnect()
{
	Agent::disconnect();
	this->castedBody = NULL;
}

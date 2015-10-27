#include "Agents/AgentReceptor.h"

AgentReceptor::AgentReceptor(Problem* problem, BodyReceptorComposition* body) : Agent(problem, body)
{
	connectCasted(body);
}

void AgentReceptor::live()
{
    //Perception p = ((BodyEmitter*)this->body).getPerception();

    //((Pendulum*)this->problem)->act(-1*p.amplitude);
}


void AgentReceptor::connectCasted(BodyReceptorComposition* body)
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

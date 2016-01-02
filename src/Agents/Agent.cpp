#include "Agents/Agent.h"



Agent::Agent(Problem* problem, Body* body, int type) : problem(problem), body(body)
{
	this->setType(type);
}

Agent::~Agent(void)
{
}

void Agent::connect(Body* body)
{
	if (body != NULL)
	{
		this->body = body;
		this->body->setBodyType(this->type);
	}
}

Body * Agent::getBody()
{
	return this->body;
}

// Checks if agent is linked to a body
bool Agent::isLinked()
{
	if (this->body == NULL)
		return false;
	return true;
}

// Cheks if agent is correctly linked to a problem
bool Agent::isProblemLinked()
{
	if (this->problem != NULL)
		return true;
	return false;
}

void Agent::disconnect()
{
	this->body = NULL;
}

void Agent::setProblem(Problem* problem)
{
	this->problem = problem;
}

Problem* Agent::getProblem()
{
	return this->problem;
}

int Agent::getType()
{
	return this->type;
}

void Agent::setType(int type)
{
	this->type = type;
	if (body != NULL)
		this->body->setBodyType(type);
}

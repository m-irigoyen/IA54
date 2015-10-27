#include "Agents/Agent.h"

Agent::Agent(Problem* problem, Body* body) : problem(problem), body(body)
{
}

Agent::~Agent(void)
{
}

void Agent::connect(Body* body)
{
	this->body = body;
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
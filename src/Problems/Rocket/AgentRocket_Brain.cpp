#include "Problems/Rocket/AgentRocket_Brain.h"

AgentRocket_Brain::AgentRocket_Brain(ProblemRocket* problem, bool active) : Agent(problem), active(active)
{
	this->desiredState.insert(pair<int, int>(0, 1));
	this->desiredState.insert(pair<int, int>(1, 0));
	this->desiredState.insert(pair<int, int>(2, 0));
	this->desiredState.insert(pair<int, int>(3, 0));
	this->desiredState.insert(pair<int, int>(4, 0));
	this->desiredState.insert(pair<int, int>(5, 0));
	this->desiredState.insert(pair<int, int>(6, 0));
}

void AgentRocket_Brain::clearDesiredState()
{
	this->desiredState.at(0) = 1;
	for (int i = 1; i <= 5; ++i)
	{
		this->desiredState.at(i) = 0;
	}
}

const map<int, int> AgentRocket_Brain::getDesiredState()
{
	return this->desiredState;
}

bool AgentRocket_Brain::isActive()
{
	return this->active;
}

void AgentRocket_Brain::setActive(bool active)
{
	this->active = active;
}

void AgentRocket_Brain::toggleActive()
{
	this->active = toggle(this->active);
}

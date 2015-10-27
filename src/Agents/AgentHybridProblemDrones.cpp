#include "Agents/AgentHybridProblemDrones.h"

AgentHybridProblemDrones::AgentHybridProblemDrones(ProblemDrones * problem, BodyHybrid * body, int droneId) : AgentHybrid(problem, body),
	droneId(droneId)
{
	this->castedProblem = problem;
}

void AgentHybridProblemDrones::live()
{
	pos3 pos;
	pos.xPos = this->body->getX() / 10;
	pos.yPos = this->body->getY() / 10;
	pos.zPos = 0.0f;
	this->castedProblem->setPos(this->droneId, pos);
}

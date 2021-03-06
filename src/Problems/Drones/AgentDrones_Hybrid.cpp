#include "Problems/Drones/AgentDrones_Hybrid.h"

AgentDrones_Hybrid::AgentDrones_Hybrid(ProblemDrones * problem, BodyHybrid * body, int droneId) : AgentHybrid(problem, body),
	droneId(droneId)
{
	this->castedProblem = problem;
}

void AgentDrones_Hybrid::live()
{
	pos3 pos;
	pos.xPos = this->body->getX() / 10;
	pos.yPos = this->body->getY() / 10;
	pos.zPos = 0.0f;
	this->castedProblem->setPos(this->droneId, pos);
}

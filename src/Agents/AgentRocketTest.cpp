#include "Agents/AgentRocketTest.h"

AgentRocketTest::AgentRocketTest(ProblemRocket * problem) : Agent(problem)
{
	this->castedProblem = problem;
}

void AgentRocketTest::live()
{
	//this->castedProblem->setPower(100);
	//this->castedProblem->addAngle(1);
}

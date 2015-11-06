#include "Agents/AgentRocketTest.h"

AgentRocketTest::AgentRocketTest(ProblemRocket * problem) : Agent(problem)
{
	this->castedProblem = problem;
}

void AgentRocketTest::connectCasted(BodyEmitter * body)
{
	if (body != NULL)
		this->castedBody = body;
	else
	{
		cout << "FUUUUUUUUUUUUUUUUUU" << endl;
	}
}

void AgentRocketTest::live()
{
	this->castedBody->send(1, 100);
	//this->castedProblem->setPower(100);
	//this->castedProblem->addAngle(1);
}

#ifndef AGENTROCKETTEST_H_
#define AGENTROCKETTEST_H_

#include "Agents/Agent.h"
#include "Problems/ProblemRocket.h"

class AgentRocketTest : public Agent
{
protected:
	ProblemRocket* castedProblem;

public:
	AgentRocketTest(ProblemRocket* problem);

	virtual void live();
};

#endif
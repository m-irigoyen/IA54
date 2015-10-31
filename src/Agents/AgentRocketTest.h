#ifndef AGENTROCKETTEST_H_
#define AGENTROCKETTEST_H_

#include "Agents/Agent.h"
#include "Problems/ProblemRocket.h"

class AgentRocketTest : public Agent
{
protected:
	ProblemRocket* castedProblem;
	BodyEmitter* castedBody;

public:
	AgentRocketTest(ProblemRocket* problem);

	virtual void connectCasted(BodyEmitter* body);

	virtual void live();
};

#endif
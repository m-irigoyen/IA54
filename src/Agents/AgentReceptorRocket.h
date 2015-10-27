#ifndef AGENTRECEPTORROCKET_H_
#define AGENTRECEPTORROCKET_H_

#include "Agents/AgentReceptor.h"
#include "Problems/ProblemRocket.h"

/*
*   AgentReceptors recieve waves in the environment, and in turn act on the problem (drone, pendulum, etc)
*/

class AgentReceptorRocket : public AgentReceptor
{
protected:
	ProblemRocket* castedProblem;

public:
	AgentReceptorRocket(ProblemRocket* problem, BodyReceptorComposition* body = NULL);

	virtual void live();
	virtual bool isLinked();
	virtual bool isProblemLinked();

	~AgentReceptorRocket(void);
};

#endif

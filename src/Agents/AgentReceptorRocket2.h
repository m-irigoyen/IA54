#ifndef AGENTRECEPTORROCKET2_H_
#define AGENTRECEPTORROCKET2_H_

#include "Agents/AgentReceptor.h"
#include "Problems/ProblemRocket2.h"

/*
*   AgentReceptors recieve waves in the environment, and in turn act on the problem (drone, pendulum, etc)
*/

class AgentReceptorRocket2 : public AgentReceptor
{
protected:
	ProblemRocket2* castedProblem;

	AGENTTYPE_ROCKET2 agentType;

public:
	AgentReceptorRocket2(ProblemRocket2* problem, BodyReceptorComposition* body = NULL, AGENTTYPE_ROCKET2 type = AGENTTYPE_ROCKET2::ROCKET2_DEFAULT);

	virtual void live();
	virtual bool isLinked();
	virtual bool isProblemLinked();

	void setAgentType(AGENTTYPE_ROCKET2 type);

	~AgentReceptorRocket2(void);
};

#endif

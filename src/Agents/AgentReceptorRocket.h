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

	AGENTTYPE_ROCKET agentType;

public:
	AgentReceptorRocket(ProblemRocket* problem, BodyReceptorFullComposition* body = NULL, AGENTTYPE_ROCKET type = AGENTTYPE_ROCKET::ROCKET_DEFAULT);

	virtual void live();
	virtual bool isLinked();
	virtual bool isProblemLinked();

	void setAgentType(AGENTTYPE_ROCKET type);

	~AgentReceptorRocket(void);
};

#endif

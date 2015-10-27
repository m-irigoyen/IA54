#ifndef AGENTRECEPTOR_H_
#define AGENTRECEPTOR_H_

#include "Agents/Agent.h"
#include "Bodies/BodyReceptorComposition.h"

/*
*   AgentReceptors recieve waves in the environment, and in turn act on the problem (drone, pendulum, etc)
*/

class AgentReceptor : public Agent
{
protected:

	BodyReceptor* castedBody;

public:
	AgentReceptor(Problem* problem, BodyReceptorComposition* body = NULL);

	virtual void live();

	virtual void connectCasted(BodyReceptorComposition* body);
	virtual void disconnect();

	~AgentReceptor(void);
};

#endif

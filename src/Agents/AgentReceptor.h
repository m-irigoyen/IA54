#ifndef AGENTRECEPTOR_H_
#define AGENTRECEPTOR_H_

#include "Agents/Agent.h"
#include "Bodies/BodyReceptor_Composition.h"
#include "Bodies/BodyReceptor_CompositionFull.h"

/*
*   AgentReceptors recieve waves in the environment, and in turn act on the problem (drone, pendulum, etc)
*/

class AgentReceptor : public Agent
{
protected:

	BodyReceptor* castedBody;

public:
	AgentReceptor(Problem* problem, BodyReceptor* body = NULL, int type = -1);

	virtual void live();

	virtual void connectCasted(BodyReceptor* body);
	virtual void disconnect();

	~AgentReceptor(void);
};

#endif

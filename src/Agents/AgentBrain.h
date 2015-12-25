#ifndef AGENTBRAIN_H_
#define AGENTBRAIN_H_

#include "Agents/Agent.h"

/*
*   AgentEmitters emit waves. They percieve the state of the problem (pendulum, drone, etc), and emit waves into the environment.
*/

class AgentBrain : public Agent
{
protected:

public:
	AgentBrain(Problem* problem);

	virtual void live() = 0;

};

#endif

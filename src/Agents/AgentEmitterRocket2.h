#ifndef AGENTEMITTERROCKET2_H_
#define AGENTEMITTERROCKET2_H_

#include "Agents/AgentEmitter.h"
#include "Problems/ProblemRocket2.h"

#define DEBUG_AGENTEMITTER_ROCKET2 1

/*
*   Emitter for the Rocket problem
*/

class AgentEmitterRocket2 : public AgentEmitter
{
protected:
	ProblemRocket2* castedProblem;

	AGENTTYPE_ROCKET2 agentType;

public:
	AgentEmitterRocket2(ProblemRocket2* problem, BodyEmitter* body = NULL, AGENTTYPE_ROCKET2 type = AGENTTYPE_ROCKET2::ROCKET2_DEFAULT);

	virtual void live();
	virtual bool isLinked();	// Checks if agent is linked to a body
	virtual bool isProblemLinked();

	void setAgentType(AGENTTYPE_ROCKET2 type);

	~AgentEmitterRocket2(void);
};

#endif

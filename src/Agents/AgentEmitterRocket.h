#ifndef AGENTEMITTERROCKET_H_
#define AGENTEMITTERROCKET_H_

#include "Agents/AgentEmitter.h"
#include "Problems/ProblemRocket.h"

#define DEBUG_AGENTEMITTER_ROCKET 1

/*
*   Emitter for the Rocket problem
*/

class AgentEmitterRocket : public AgentEmitter
{
protected:
	ProblemRocket* castedProblem;

	AGENTTYPE_ROCKET agentType;

public:
	AgentEmitterRocket(ProblemRocket* problem, BodyEmitter* body = NULL, AGENTTYPE_ROCKET type = AGENTTYPE_ROCKET::ROCKET_DEFAULT);

	virtual void live();
	virtual bool isLinked();	// Checks if agent is linked to a body
	virtual bool isProblemLinked();

	void setAgentType(AGENTTYPE_ROCKET type);

	~AgentEmitterRocket(void);
};

#endif

#ifndef PROBLEMROCKET_ONEENGINE_EMITTER_H_
#define PROBLEMROCKET_ONEENGINE_EMITTER_H_

#include "Agents/AgentEmitter.h"
#include "Problems/Rocket/OneEngine/ProblemRocket_OneEngine.h"


/*
*   Emitter for the hard set one engine rocket problem
*/

class AgentRocket_OneEngine_Emitter : public AgentEmitter
{
protected:
	ProblemRocket_OneEngine* castedProblem;

	AGENTTYPE_ROCKET_ONE agentType;

public:
	AgentRocket_OneEngine_Emitter(ProblemRocket_OneEngine* problem, BodyEmitter* body = NULL, AGENTTYPE_ROCKET_ONE type = AGENTTYPE_ROCKET_ONE::ROCKET_ONE_DEFAULT);

	virtual void live();
	virtual bool isLinked();	// Checks if agent is linked to a body
	virtual bool isProblemLinked();

	void setAgentType(AGENTTYPE_ROCKET_ONE type);

	~AgentRocket_OneEngine_Emitter(void);
};

#endif

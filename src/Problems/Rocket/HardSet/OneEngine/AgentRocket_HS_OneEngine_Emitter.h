#ifndef PROBLEMROCKET_HS_ONEENGINE_EMITTER_H_
#define PROBLEMROCKET_HS_ONEENGINE_EMITTER_H_

#include "Agents/AgentEmitter.h"
#include "Problems/Rocket/HardSet/OneEngine/ProblemRocket_HS_OneEngine.h"

/*
*   Emitter for the hard set one engine rocket problem
*/

class AgentRocket_HS_OneEngine_Emitter : public AgentEmitter
{
protected:
	ProblemRocket_HS_OneEngine* castedProblem;

	AGENTTYPE_ROCKET_HS_ONE agentType;

public:
	AgentRocket_HS_OneEngine_Emitter(ProblemRocket_HS_OneEngine* problem, BodyEmitter* body = NULL, AGENTTYPE_ROCKET_HS_ONE type = AGENTTYPE_ROCKET_HS_ONE::ROCKET_HS_ONE_DEFAULT);

	virtual void live();
	virtual bool isLinked();	// Checks if agent is linked to a body
	virtual bool isProblemLinked();

	void setAgentType(AGENTTYPE_ROCKET_HS_ONE type);

	~AgentRocket_HS_OneEngine_Emitter(void);
};

#endif

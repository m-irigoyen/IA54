#ifndef PROBLEMROCKET_HS_TWOENGINES_EMITTER_H_
#define PROBLEMROCKET_HS_TWOENGINES_EMITTER_H_

#include "Agents/AgentEmitter.h"
#include "Problems/Rocket/HardSet/TwoEngines/ProblemRocket_HS_TwoEngines.h"

#define DEBUG_AGENTEMITTER_ROCKET2 1

/*
*   Emitter for the Rocket problem
*/

class AgentRocket_HS_TwoEngines_Emitter : public AgentEmitter
{
protected:
	ProblemRocket_HS_TwoEngines* castedProblem;

	AGENTTYPE_ROCKET_HS_TWO agentType;

public:
	AgentRocket_HS_TwoEngines_Emitter(ProblemRocket_HS_TwoEngines* problem, BodyEmitter* body = NULL, AGENTTYPE_ROCKET_HS_TWO type = AGENTTYPE_ROCKET_HS_TWO::ROCKET_HS_TWO_DEFAULT);

	virtual void live();
	virtual bool isLinked();	// Checks if agent is linked to a body
	virtual bool isProblemLinked();

	void setAgentType(AGENTTYPE_ROCKET_HS_TWO type);

	~AgentRocket_HS_TwoEngines_Emitter(void);
};

#endif

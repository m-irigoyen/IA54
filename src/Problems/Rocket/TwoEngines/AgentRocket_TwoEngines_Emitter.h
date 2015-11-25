#ifndef PROBLEMROCKET_TWOENGINES_EMITTER_H_
#define PROBLEMROCKET_TWOENGINES_EMITTER_H_

#include "Agents/AgentEmitter.h"
#include "Problems/Rocket/TwoEngines/ProblemRocket_TwoEngines.h"

#define DEBUG_AGENTEMITTER_ROCKET2 1

/*
*   Emitter for the Rocket problem
*/

class AgentRocket_TwoEngines_Emitter : public AgentEmitter
{
protected:
	ProblemRocket_TwoEngines* castedProblem;

	AGENTTYPE_ROCKET_TWO agentType;

	void tendToDesiredAngle(float desiredAngle, float currentAngle, float& lPowerChange, float& rPowerChange);

public:
	AgentRocket_TwoEngines_Emitter(ProblemRocket_TwoEngines* problem, BodyEmitter* body = NULL, AGENTTYPE_ROCKET_TWO type = AGENTTYPE_ROCKET_TWO::ROCKET_TWO_STABILIZER);

	virtual void live();
	virtual bool isLinked();	// Checks if agent is linked to a body
	virtual bool isProblemLinked();

	void setAgentType(AGENTTYPE_ROCKET_TWO type);

	~AgentRocket_TwoEngines_Emitter(void);
};

#endif

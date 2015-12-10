#ifndef PROBLEMROCKET_TWOENGINES_RECEPTOR_H_
#define PROBLEMROCKET_TWOENGINES_RECEPTOR_H_

#include "Agents/AgentReceptor.h"
#include "Problems/Rocket/TwoEngines/ProblemRocket_TwoEngines.h"

/*
*   AgentReceptors recieve waves in the environment, and in turn act on the problem (drone, pendulum, etc)
*/

class AgentRocket_TwoEngines_Receptor : public AgentReceptor
{
protected:
	ProblemRocket_TwoEngines* castedProblem;

	AGENTTYPE_ROCKET_TWO agentType;

public:
	AgentRocket_TwoEngines_Receptor(ProblemRocket_TwoEngines* problem, BodyReceptor_Composition* body = NULL, AGENTTYPE_ROCKET_TWO type = AGENTTYPE_ROCKET_TWO::ROCKET_TWO_STABILIZER_ANGLE);

	virtual void live();
	virtual bool isLinked();
	virtual bool isProblemLinked();

	void setAgentType(AGENTTYPE_ROCKET_TWO type);

	~AgentRocket_TwoEngines_Receptor(void);
};

#endif

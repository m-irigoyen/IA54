#ifndef PROBLEMROCKET_HS_TWOENGINES_RECEPTOR_H_
#define PROBLEMROCKET_HS_TWOENGINES_RECEPTOR_H_

#include "Agents/AgentReceptor.h"
#include "Problems/Rocket/HardSet/TwoEngines/ProblemRocket_HS_TwoEngines.h"

/*
*   AgentReceptors recieve waves in the environment, and in turn act on the problem (drone, pendulum, etc)
*/

class AgentRocket_HS_TwoEngines_Receptor : public AgentReceptor
{
protected:
	ProblemRocket_HS_TwoEngines* castedProblem;

	AGENTTYPE_ROCKET_HS_TWO agentType;

public:
	AgentRocket_HS_TwoEngines_Receptor(ProblemRocket_HS_TwoEngines* problem, BodyReceptor_Composition* body = NULL, AGENTTYPE_ROCKET_HS_TWO type = AGENTTYPE_ROCKET_HS_TWO::ROCKET_HS_TWO_DEFAULT);

	virtual void live();
	virtual bool isLinked();
	virtual bool isProblemLinked();

	void setAgentType(AGENTTYPE_ROCKET_HS_TWO type);

	~AgentRocket_HS_TwoEngines_Receptor(void);
};

#endif

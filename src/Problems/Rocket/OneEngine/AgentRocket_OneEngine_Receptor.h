#ifndef PROBLEMROCKET_HS_ONEENGINE_RECEPTOR_H_
#define PROBLEMROCKET_HS_ONEENGINE_RECEPTOR_H_

#include "Agents/AgentReceptor.h"
#include "Problems/Rocket/HardSet/OneEngine/ProblemRocket_HS_OneEngine.h"

/*
*   AgentReceptors recieve waves in the environment, and in turn act on the problem (drone, pendulum, etc)
*/

class AgentRocket_HS_OneEngine_Receptor : public AgentReceptor
{
protected:
	ProblemRocket_HS_OneEngine* castedProblem;

	AGENTTYPE_ROCKET_HS_ONE agentType;

public:

	AgentRocket_HS_OneEngine_Receptor(ProblemRocket_HS_OneEngine* problem, BodyReceptor_CompositionFull* body = NULL, AGENTTYPE_ROCKET_HS_ONE type = AGENTTYPE_ROCKET_HS_ONE::ROCKET_HS_ONE_DEFAULT);

	virtual void live();
	virtual bool isLinked();
	virtual bool isProblemLinked();

	void setAgentType(AGENTTYPE_ROCKET_HS_ONE type);

	~AgentRocket_HS_OneEngine_Receptor(void);
};

#endif

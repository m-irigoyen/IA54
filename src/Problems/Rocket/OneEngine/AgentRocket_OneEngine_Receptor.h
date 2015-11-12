#ifndef PROBLEMROCKET_ONEENGINE_RECEPTOR_H_
#define PROBLEMROCKET_ONEENGINE_RECEPTOR_H_

#include "Agents/AgentReceptor.h"
#include "Problems/Rocket/OneEngine/ProblemRocket_OneEngine.h"

/*
*   AgentReceptors recieve waves in the environment, and in turn act on the problem (drone, pendulum, etc)
*/

class AgentRocket_OneEngine_Receptor : public AgentReceptor
{
protected:
	ProblemRocket_OneEngine* castedProblem;

	PROBLEMROCKET_AGENTTYPE_ONE agentType;

public:

	AgentRocket_OneEngine_Receptor(ProblemRocket_OneEngine* problem, BodyReceptor_CompositionFull* body = NULL, PROBLEMROCKET_AGENTTYPE_ONE type = PROBLEMROCKET_AGENTTYPE_ONE::ROCKET_HS_ONE_DEFAULT);

	virtual void live();
	virtual bool isLinked();
	virtual bool isProblemLinked();

	void setAgentType(PROBLEMROCKET_AGENTTYPE_ONE type);

	~AgentRocket_OneEngine_Receptor(void);
};

#endif

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

public:

	AgentRocket_OneEngine_Receptor(ProblemRocket_OneEngine* problem, BodyReceptor_CompositionFull* body = NULL, AGENTTYPE_ROCKET_ONE type = AGENTTYPE_ROCKET_ONE::ROCKET_ONE_RECEPTOR);

	virtual void live();
	virtual bool isLinked();
	virtual bool isProblemLinked();

};

#endif

#ifndef PROBLEMROCKET_ONEENGINE_BRAIN_H_
#define PROBLEMROCKET_ONEENGINE_BRAIN_H_

#include <map>

#include "Problems/Rocket/AgentRocket_Brain.h"
#include "Problems/Rocket/OneEngine/ProblemRocket_OneEngine.h"


/*
*   Emitter for the hard set one engine rocket problem
*/

class AgentRocket_OneEngine_Brain : public AgentRocket_Brain
{
protected:
	ProblemRocket_OneEngine* castedProblem;

public:
	AgentRocket_OneEngine_Brain(ProblemRocket_OneEngine* problem, bool active = true);

	virtual void live();
	virtual bool isProblemLinked();
};

#endif

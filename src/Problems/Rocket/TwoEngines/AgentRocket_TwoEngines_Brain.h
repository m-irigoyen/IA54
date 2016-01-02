#ifndef PROBLEMROCKET_TWOENGINES_BRAIN_H_
#define PROBLEMROCKET_TWOENGINES_BRAIN_H_

#include "Problems/Rocket/AgentRocket_Brain.h"
#include "Problems/Rocket/TwoEngines/ProblemRocket_TwoEngines.h"

/*
*   Brain for the Rocket problem
*/

class AgentRocket_TwoEngines_Brain : public AgentRocket_Brain
{
protected:
	ProblemRocket_TwoEngines* castedProblem;

public:
	AgentRocket_TwoEngines_Brain(ProblemRocket_TwoEngines* problem, bool active = true);

	virtual void live();
	virtual bool isProblemLinked();
};

#endif

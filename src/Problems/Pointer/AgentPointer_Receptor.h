#ifndef AGENTRECEPTORPROBLEMPOINTER_H_
#define AGENTRECEPTORPROBLEMPOINTER_H_

#define DEBUG_AGENTRECEPTORPROBLEMPOINTER 1

#include "Agents/AgentReceptor.h"
#include "Problems/Pointer/ProblemPointer.h"

/*
*   AgentReceptors recieve waves in the environment, and in turn act on the problem (drone, pendulum, etc)
*/

class AgentPointer_Receptor : public AgentReceptor
{
protected:
	ProblemPointer* castedProblem;

public:
	AgentPointer_Receptor(ProblemPointer* problem, BodyReceptor_Composition* body = NULL);

	virtual void live();
	virtual bool isLinked();
	virtual bool isProblemLinked();



	~AgentPointer_Receptor(void);
};

#endif

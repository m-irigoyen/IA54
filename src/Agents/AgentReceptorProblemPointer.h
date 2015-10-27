#ifndef AGENTRECEPTORPROBLEMPOINTER_H_
#define AGENTRECEPTORPROBLEMPOINTER_H_

#define DEBUG_AGENTRECEPTORPROBLEMPOINTER 1

#include "Agents/AgentReceptor.h"
#include "Problems/ProblemPointer.h"

/*
*   AgentReceptors recieve waves in the environment, and in turn act on the problem (drone, pendulum, etc)
*/

class AgentReceptorProblemPointer : public AgentReceptor
{
protected:
	ProblemPointer* castedProblem;

public:
	AgentReceptorProblemPointer(ProblemPointer* problem, BodyReceptorComposition* body = NULL);

	virtual void live();
	virtual bool isLinked();
	virtual bool isProblemLinked();



	~AgentReceptorProblemPointer(void);
};

#endif

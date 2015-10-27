#ifndef AGENTEMITTERPROBLEMPOINTER_H_
#define AGENTEMITTERPROBLEMPOINTER_H_

#include "Agents/AgentEmitter.h"
#include "Problems/ProblemPointer.h"

#define DEBUG_AGENTEMITTERPROBLEMPOINTER 1

/*
*   Emitter for the ProblemPointer
*/

class AgentEmitterProblemPointer : public AgentEmitter
{
protected:
	ProblemPointer* castedProblem;

public:
	AgentEmitterProblemPointer(ProblemPointer* problem, BodyEmitter* body = NULL);

	virtual void live();
	virtual bool isLinked();	// Checks if agent is linked to a body
	virtual bool isProblemLinked();

	~AgentEmitterProblemPointer(void);
};

#endif

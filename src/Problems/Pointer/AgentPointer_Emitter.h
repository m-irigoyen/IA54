#ifndef AGENTEMITTERPROBLEMPOINTER_H_
#define AGENTEMITTERPROBLEMPOINTER_H_

#include "Agents/AgentEmitter.h"
#include "Problems/Pointer/ProblemPointer.h"

#define DEBUG_AGENTEMITTERPROBLEMPOINTER 1

/*
*   Emitter for the ProblemPointer
*/

class AngetPointer_Emitter : public AgentEmitter
{
protected:
	ProblemPointer* castedProblem;

public:
	AngetPointer_Emitter(ProblemPointer* problem, BodyEmitter* body = NULL);

	virtual void live();
	virtual bool isLinked();	// Checks if agent is linked to a body
	virtual bool isProblemLinked();

	~AngetPointer_Emitter(void);
};

#endif

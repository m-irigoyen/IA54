#ifndef AGENTHYBRIDPROBLEMDRONES_H_
#define AGENTHYBRIDPROBLEMDRONES_H_

#include "Problems/Drones/ProblemDrones.h"
#include "Agents/AgentHybrid.h"

/*
*   Hybrid for the ProblemPointer
*/

class AgentDrones_Hybrid : public AgentHybrid
{
protected:
	ProblemDrones* castedProblem;
	int droneId;

public:
	AgentDrones_Hybrid(ProblemDrones* problem, BodyHybrid* body = NULL, int droneId = -1);

	virtual void live();

	void connectEmitter();

	~AgentDrones_Hybrid(void);
};

#endif

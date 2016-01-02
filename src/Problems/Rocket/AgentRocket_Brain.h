#ifndef AGENTROCKET_BRAIN_H_
#define AGENTROCKET_BRAIN_H_

#include <map>

#include "Agents/Agent.h"
#include "Problems/Rocket/ProblemRocket.h"
#include "Utilities/MathHelper.h"


/*
*   Emitter for the hard set one engine rocket problem
*/

class AgentRocket_Brain : public Agent
{
protected:
	map<int, int> desiredState;
	bool active;

public:
	AgentRocket_Brain(ProblemRocket* problem, bool active = true);

	virtual void live() = 0;
	void clearDesiredState();
	const map<int, int> getDesiredState();

	bool isActive();
	void setActive(bool active);
	void toggleActive();
};

#endif

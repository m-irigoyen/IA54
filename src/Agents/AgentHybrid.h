#ifndef AGENTHYBRID_H_
#define AGENTHYBRID_H_

#include "Agents/Agent.h"
#include "Bodies/BodyHybrid.h"

/*
*   AgentHybrid : an hybrid that can both emit and receive
*/

class AgentHybrid : public Agent
{
protected:
	//int state;

	BodyHybrid* castedBody;

public:
	AgentHybrid(Problem* problem, BodyHybrid* body = NULL);

	virtual void live() = 0;

	virtual void connectCasted(BodyHybrid* body);
	virtual void disconnect();

	~AgentHybrid(void);
};

#endif

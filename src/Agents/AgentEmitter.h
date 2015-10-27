#ifndef AGENTEMITTER_H_
#define AGENTEMITTER_H_

#include "Agents/Agent.h"

/*
*   AgentEmitters emit waves. They percieve the state of the problem (pendulum, drone, etc), and emit waves into the environment.
*/

class AgentEmitter : public Agent
{
protected:
	//int state;

	BodyEmitter* castedBody;

public:
	AgentEmitter(Problem* problem, BodyEmitter* body = NULL);

	virtual void live() = 0;

	virtual void connectCasted(BodyEmitter* body);
	virtual void disconnect();

	~AgentEmitter(void);
};

#endif

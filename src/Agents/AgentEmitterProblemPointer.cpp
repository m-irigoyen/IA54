#include "Agents/AgentEmitterProblemPointer.h"

AgentEmitterProblemPointer::AgentEmitterProblemPointer(ProblemPointer* problem, BodyEmitter* body) : AgentEmitter(problem, body), castedProblem(problem)
{

}

void AgentEmitterProblemPointer::live()
{
	if (!this->isLinked())
	{
		std::cout << "ERROR : AgentEmitterProblemPointer::live : agent isn't linked to a body" << std::endl;
		return;
	}
	else if (!this->isProblemLinked())
	{
		std::cout << "ERROR : AgentEmitterProblemPointer::live : agent isn't linked to a problem" << std::endl;
		return;
	}

	float mouseX, mouseY;
	int windowWidth, windowHeight;

	this->castedProblem->getMousePointerPosition(mouseX, mouseY);
	this->castedProblem->getWindowDimensions(windowWidth, windowHeight);

	// Encoding x/y position
	double frequency = ((mouseX)*FREQUENCY_RANGE / (double)windowWidth) + this->castedProblem->getFrequencyOffset();	// offsetting a bit, to make sure wave transmission is kept
	double amplitude = ((mouseY)*AMPLITUDE_RANGE / (double)windowHeight) + AMPLITUDE_OFFSET;
		
	this->castedBody->send(frequency, amplitude);

	//std::cout << "Emitting : " << frequency << ", " << amplitude << std::endl;;
	//this->castedBody->send(1.0f, 1.0f);
}

// Checks if agent is linked to a body
bool AgentEmitterProblemPointer::isProblemLinked()
{
	if (Agent::isProblemLinked() && this->castedProblem != NULL)
		return true;
	return false;

}

bool AgentEmitterProblemPointer::isLinked()
{
	if (Agent::isLinked() && this->castedBody != NULL)
		return true;
	return false;
}

AgentEmitterProblemPointer::~AgentEmitterProblemPointer(void)
{

}

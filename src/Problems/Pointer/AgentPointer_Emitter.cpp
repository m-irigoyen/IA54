#include "Problems/Pointer/AgentPointer_Emitter.h"

AngetPointer_Emitter::AngetPointer_Emitter(ProblemPointer* problem, BodyEmitter* body) : AgentEmitter(problem, body), castedProblem(problem)
{

}

void AngetPointer_Emitter::live()
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
	float frequency = ((mouseX)*FREQUENCY_RANGE / (float)windowWidth) + this->castedProblem->getFrequencyOffset();	// offsetting a bit, to make sure wave transmission is kept
	float amplitude = ((mouseY)*AMPLITUDE_RANGE / (float)windowHeight) + AMPLITUDE_OFFSET;
		
	this->castedBody->send(frequency, amplitude);

	//std::cout << "Emitting : " << frequency << ", " << amplitude << std::endl;;
	//this->castedBody->send(1.0f, 1.0f);
}

// Checks if agent is linked to a body
bool AngetPointer_Emitter::isProblemLinked()
{
	if (Agent::isProblemLinked() && this->castedProblem != NULL)
		return true;
	return false;

}

bool AngetPointer_Emitter::isLinked()
{
	if (Agent::isLinked() && this->castedBody != NULL)
		return true;
	return false;
}

AngetPointer_Emitter::~AngetPointer_Emitter(void)
{

}

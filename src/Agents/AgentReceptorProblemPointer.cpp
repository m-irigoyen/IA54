#include "Agents/AgentReceptorProblemPointer.h"

AgentReceptorProblemPointer::AgentReceptorProblemPointer(ProblemPointer* problem, BodyReceptorComposition* body) : AgentReceptor(problem, body), castedProblem(problem)
{

}

void AgentReceptorProblemPointer::live()
{
	if (!this->isLinked())
	{
		std::cout << "ERROR : AgentReceptorProblemPointer::live : agent isn't linked to a body" << std::endl;
		return;
	}
	else if (!this->isProblemLinked())
	{
		std::cout << "ERROR : AgentReceptorProblemPointer::live : agent isn't linked to a problem" << std::endl;
		return;
	}

	WAVE_COMPOSITION perception = this->castedBody->getPerception();

	float mouseX, mouseY;
	int windowWidth, windowHeight;

	this->castedProblem->getWindowDimensions(windowWidth, windowHeight);

	// Decoding x/y position
	perception.frequency -= this->castedProblem->getFrequencyOffset();
	mouseX = (perception.frequency * windowWidth) / FREQUENCY_RANGE;

	perception.amplitude -= AMPLITUDE_OFFSET;
	mouseY = (perception.amplitude * windowHeight) / AMPLITUDE_RANGE;

	this->castedProblem->setSecondPointerPosition(mouseX, mouseY);
	//this->castedProblem->setSecondPointerPosition(50, mouseY);
	//std::cout << "Percieved : " << perception.frequency << " | " << perception.amplitude << " -> " << mouseX << " | " << mouseY << std::endl;
}

bool AgentReceptorProblemPointer::isLinked()
{
	if (Agent::isLinked() && this->castedBody != NULL)
		return true;
	return false;
}

bool AgentReceptorProblemPointer::isProblemLinked()
{
	if (Agent::isProblemLinked() && this->castedProblem != NULL)
	{
		return true;
	}
	return false;
}

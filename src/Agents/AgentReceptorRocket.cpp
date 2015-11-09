#include "Agents/AgentReceptorRocket.h"

AgentReceptorRocket::AgentReceptorRocket(ProblemRocket * problem, BodyReceptorComposition * body, AGENTTYPE_ROCKET type) : AgentReceptor(problem,body), castedProblem(problem), agentType(type)
{
}

void AgentReceptorRocket::live()
{
	// Getting perception from body
	WAVE_COMPOSITION perception = this->castedBody->getPerception();

	// Getting angle back
	perception.amplitude -= ROCKET_WAVE_AMPLITUDE_OFFSET;
	double angle = (perception.amplitude * (ROCKET_PROBLEM_MAXANGLE * 2)) / ROCKET_WAVE_AMPLITUDE_RANGE;	// 0 <= angle <= 2 * maxAngle
	angle -= ROCKET_PROBLEM_MAXANGLE;	// Correcting to -maxAngle <= angle <= maxAngle

	// Getting frequency back
	double power = (perception.frequency * (ROCKET_SPECS_POWER_MAX)) / ROCKET_WAVE_FREQUENCY_RANGE;

	this->castedProblem->setAngle(angle);
	this->castedProblem->setPower(power);
}

bool AgentReceptorRocket::isLinked()
{
	return AgentReceptor::isLinked();
}

bool AgentReceptorRocket::isProblemLinked()
{
	return this->castedProblem != NULL;
}

void AgentReceptorRocket::setAgentType(AGENTTYPE_ROCKET type)
{
	this->agentType = type;
}

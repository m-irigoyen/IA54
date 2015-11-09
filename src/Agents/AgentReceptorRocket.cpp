#include "Agents/AgentReceptorRocket.h"

AgentReceptorRocket::AgentReceptorRocket(ProblemRocket * problem, BodyReceptorComposition * body, AGENTTYPE_ROCKET type) : AgentReceptor(problem,body), castedProblem(problem), agentType(type)
{
}

void AgentReceptorRocket::live()
{
	if (!this->problem->getProblemLive())
		return;

	// Getting perception from body
	WAVE_COMPOSITION perception = this->castedBody->getPerception();

	// Getting angle back
	cout << "Perceived amplitude : " << perception.amplitude << endl;
	perception.amplitude -= ROCKET_WAVE_AMPLITUDE_OFFSET;

	cout << "Perceived amplitude : " << perception.amplitude << endl;
	
	double angle = (perception.amplitude * (ROCKET_PROBLEM_MAXANGLE * 2)) / ROCKET_WAVE_AMPLITUDE_RANGE;	// 0 <= angle <= 2 * maxAngle
	cout << "Preliminary angle : " << angle <<  endl;
	angle -= ROCKET_PROBLEM_MAXANGLE;	// Correcting to -maxAngle <= angle <= maxAngle

	// Getting frequency back
	double power = (perception.frequency * (ROCKET_SPECS_POWER_MAX)) / ROCKET_WAVE_FREQUENCY_RANGE;

	this->castedProblem->setAngle(angle);
	this->castedProblem->setPower(power);

	cout << "RECEIVING : " << angle << ", " << power << endl;
	cout << endl;
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

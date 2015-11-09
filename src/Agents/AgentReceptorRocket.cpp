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

	cout << "RECEIVED : " << perception.frequency << ", " << perception.amplitude << endl;
	double angle = this->convertToRange(perception.amplitude,
		ROCKET_WAVE_AMPLITUDE_RANGE,
		ROCKET_WAVE_AMPLITUDE_OFFSET,
		ROCKET_PROBLEM_MAXANGLE * 2,
		0);
	angle -= ROCKET_PROBLEM_MAXANGLE;

	// Getting frequency back
	perception.frequency -= ROCKET_WAVE_FREQUENCY_OFFSET;
	double power = this->convertToRange(perception.frequency,
		ROCKET_WAVE_FREQUENCY_RANGE,
		ROCKET_WAVE_FREQUENCY_OFFSET,
		ROCKET_SPECS_POWER_MAX,
		0);

	cout << "TRANSLATED : " << power << ", " << angle << endl << endl;
	
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

#include "Problems/Rocket/TwoEngines/AgentRocket_TwoEngines_Receptor.h"

AgentRocket_TwoEngines_Receptor::AgentRocket_TwoEngines_Receptor(ProblemRocket_TwoEngines * problem, BodyReceptor_Composition * body, AGENTTYPE_ROCKET_TWO type) : AgentReceptor(problem,body), castedProblem(problem), agentType(type)
{
}

void AgentRocket_TwoEngines_Receptor::live()
{
	if (this->castedProblem->getUserControlled() || !this->problem->getProblemLive())
		return;

	// Getting perception from body
	WAVE perception = this->castedBody->getPerception();

	// Checking error in parameters
	if (perception.amplitude < this->castedProblem->getWaveAmplitudeOffset())
	{
		perception.amplitude = this->castedProblem->getWaveAmplitudeOffset();
		//cout << "ERROR : AgentReceptorRocket::Live : amplitude was sub offset" << endl;
	}
	else if (perception.amplitude >(this->castedProblem->getWaveAmplitudeOffset() + this->castedProblem->getWaveAmplitudeRange()))
	{
		perception.amplitude = this->castedProblem->getWaveAmplitudeOffset() + this->castedProblem->getWaveAmplitudeRange();
		//cout << "ERROR : AgentReceptorRocket::Live : amplitude was bigger than range + offset" << endl;
	}

	if (perception.frequency < this->castedProblem->getWaveFrequencyOffset())
	{
		perception.frequency = this->castedProblem->getWaveFrequencyOffset();
		//cout << "ERROR : AgentReceptorRocket::Live : frequency was sub offset" << endl;
	}
	else if (perception.frequency >(this->castedProblem->getWaveFrequencyOffset() + this->castedProblem->getWaveFrequencyRange()))
	{
		perception.frequency = this->castedProblem->getWaveFrequencyOffset() + this->castedProblem->getWaveFrequencyRange();
		//cout << "ERROR : AgentReceptorRocket::Live : frequency was bigger than range + offset" << endl;
	}

	// Converting into angle and power values
	//cout << "RECEIVED : " << perception.frequency << ", " << perception.amplitude << endl;
	float powerL = convertToRange(perception.amplitude,
		this->castedProblem->getWaveAmplitudeOffset(),
		this->castedProblem->getWaveAmplitudeRange(),
		0,
		this->castedProblem->getPowerMax() * 2);
	powerL -= this->castedProblem->getPowerMax();

	// Getting frequency back
	//perception.frequency -= this->castedProblem->getWaveFrequencyOffset();
	float powerR = convertToRange(perception.frequency,
		this->castedProblem->getWaveFrequencyOffset(),
		this->castedProblem->getWaveFrequencyRange(),
		0,
		this->castedProblem->getPowerMax() * 2);
	powerR -= this->castedProblem->getPowerMax();

	//cout << "TRANSLATED : " << power << ", " << angle << endl << endl;

	this->castedProblem->setDesiredPower(0, powerL);
	this->castedProblem->setDesiredPower(1, powerR);
}

bool AgentRocket_TwoEngines_Receptor::isLinked()
{
	return AgentReceptor::isLinked();
}

bool AgentRocket_TwoEngines_Receptor::isProblemLinked()
{
	return this->castedProblem != NULL;
}

void AgentRocket_TwoEngines_Receptor::setAgentType(AGENTTYPE_ROCKET_TWO type)
{
	this->agentType = type;
}

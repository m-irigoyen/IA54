#include "Problems/Rocket/OneEngine/AgentRocket_OneEngine_Receptor.h"

AgentRocket_OneEngine_Receptor::AgentRocket_OneEngine_Receptor(ProblemRocket_OneEngine * problem, BodyReceptor_CompositionFull* body, AGENTTYPE_ROCKET_ONE type) : AgentReceptor(problem,body, (int)type), castedProblem(problem)
{
}

void AgentRocket_OneEngine_Receptor::live()
{
	if (this->castedProblem->getUserControlled() || !this->problem->getProblemLive())
		return;

	// Getting perception from body
	PerceptionWave::WAVE perception = this->castedBody->getPerception();

	// Checking error in parameters
	if (perception.amplitude < this->castedProblem->getWaveAmplitudeOffset())
	{
		perception.amplitude = this->castedProblem->getWaveAmplitudeOffset();
		//cout << "ERROR : AgentReceptorRocket::Live : amplitude was sub offset" << endl;
	}
	else if (perception.amplitude > (this->castedProblem->getWaveAmplitudeOffset() + this->castedProblem->getWaveAmplitudeRange()))
	{
		perception.amplitude = this->castedProblem->getWaveAmplitudeOffset() + this->castedProblem->getWaveAmplitudeRange();
		//cout << "ERROR : AgentReceptorRocket::Live : amplitude was bigger than range + offset" << endl;
	}

	if (perception.frequency < this->castedProblem->getWaveFrequencyOffset())
	{
		perception.frequency = this->castedProblem->getWaveFrequencyOffset();
		//cout << "ERROR : AgentReceptorRocket::Live : frequency was sub offset" << endl;
	}
	else if (perception.frequency > (this->castedProblem->getWaveFrequencyOffset() + this->castedProblem->getWaveFrequencyRange()))
	{
		perception.frequency = this->castedProblem->getWaveFrequencyOffset() + this->castedProblem->getWaveFrequencyRange();
		//cout << "ERROR : AgentReceptorRocket::Live : frequency was bigger than range + offset" << endl;
	}

	// Converting into angle and power values
	//cout << "RECEIVED : " << perception.frequency << ", " << perception.amplitude << endl;
	float angle = convertToRange(perception.amplitude,
		this->castedProblem->getWaveAmplitudeOffset(),
		this->castedProblem->getWaveAmplitudeRange(),
		0,
		PROBLEMROCKET_ROCKET_ANGLE_TILT * 2);
	angle -= PROBLEMROCKET_ROCKET_ANGLE_TILT;

	// Getting frequency back
	//perception.frequency -= this->castedProblem->getWaveFrequencyOffset();
	float power = convertToRange(perception.frequency,
		this->castedProblem->getWaveFrequencyOffset(),
		this->castedProblem->getWaveFrequencyRange(),
		0,
		this->castedProblem->getPowerMax()*2);
	power -= this->castedProblem->getPowerMax();

	//cout << "TRANSLATED : " << power << ", " << angle << endl << endl;
	
	this->castedProblem->setDesiredAngle(angle);
	this->castedProblem->setDesiredPower(0, power);
}

bool AgentRocket_OneEngine_Receptor::isLinked()
{
	return AgentReceptor::isLinked();
}

bool AgentRocket_OneEngine_Receptor::isProblemLinked()
{
	return this->castedProblem != NULL;
}

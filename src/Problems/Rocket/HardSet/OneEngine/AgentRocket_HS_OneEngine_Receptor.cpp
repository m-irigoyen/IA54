#include "Problems/Rocket/HardSet/OneEngine/AgentRocket_HS_OneEngine_Receptor.h"

AgentRocket_HS_OneEngine_Receptor::AgentRocket_HS_OneEngine_Receptor(ProblemRocket_HS_OneEngine * problem, BodyReceptor_CompositionFull* body, AGENTTYPE_ROCKET_HS_ONE type) : AgentReceptor(problem,body), castedProblem(problem), agentType(type)
{
}

void AgentRocket_HS_OneEngine_Receptor::live()
{
	if (!this->problem->getProblemLive())
		return;

	// Getting perception from body
	WAVE_COMPOSITION perception = this->castedBody->getPerception();
	perception.amplitude = perception.amplitude / this->castedProblem->getNumberOfEmitters();
	perception.frequency = perception.frequency / this->castedProblem->getNumberOfEmitters();

	// Checking error in parameters
	if (perception.amplitude < ROCKET_WAVE_AMPLITUDE_OFFSET)
	{
		perception.amplitude = ROCKET_WAVE_AMPLITUDE_OFFSET;
		cout << "ERROR : AgentReceptorRocket::Live : amplitude was sub offset" << endl;
	}
	else if (perception.amplitude > (ROCKET_WAVE_AMPLITUDE_OFFSET + ROCKET_WAVE_AMPLITUDE_RANGE))
	{
		perception.amplitude = ROCKET_WAVE_AMPLITUDE_OFFSET + ROCKET_WAVE_AMPLITUDE_RANGE;
		cout << "ERROR : AgentReceptorRocket::Live : amplitude was bigger than range + offset" << endl;
	}

	if (perception.frequency < ROCKET_WAVE_FREQUENCY_OFFSET)
	{
		perception.frequency = ROCKET_WAVE_FREQUENCY_OFFSET;
		cout << "ERROR : AgentReceptorRocket::Live : frequency was sub offset" << endl;
	}
	else if (perception.frequency > (ROCKET_WAVE_FREQUENCY_OFFSET + ROCKET_WAVE_FREQUENCY_RANGE))
	{
		perception.frequency = ROCKET_WAVE_FREQUENCY_OFFSET + ROCKET_WAVE_FREQUENCY_RANGE;
		cout << "ERROR : AgentReceptorRocket::Live : frequency was bigger than range + offset" << endl;
	}


	// Converting into angle and power values
	//cout << "RECEIVED : " << perception.frequency << ", " << perception.amplitude << endl;
	double angle = this->convertToRange(perception.amplitude,
		ROCKET_WAVE_AMPLITUDE_OFFSET,
		ROCKET_WAVE_AMPLITUDE_RANGE,
		0,
		ROCKET_PROBLEM_MAXANGLE * 2);
	angle -= ROCKET_PROBLEM_MAXANGLE;

	// Getting frequency back
	//perception.frequency -= ROCKET_WAVE_FREQUENCY_OFFSET;
	double power = this->convertToRange(perception.frequency,
		ROCKET_WAVE_FREQUENCY_OFFSET,
		ROCKET_WAVE_FREQUENCY_RANGE,
		0,
		ROCKET_SPECS_POWER_MAX);

	//cout << "TRANSLATED : " << power << ", " << angle << endl << endl;
	
	this->castedProblem->setAngle(angle);
	this->castedProblem->setPower(power);
}

bool AgentRocket_HS_OneEngine_Receptor::isLinked()
{
	return AgentReceptor::isLinked();
}

bool AgentRocket_HS_OneEngine_Receptor::isProblemLinked()
{
	return this->castedProblem != NULL;
}

void AgentRocket_HS_OneEngine_Receptor::setAgentType(AGENTTYPE_ROCKET_HS_ONE type)
{
	this->agentType = type;
}


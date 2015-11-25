#include "Problems/Rocket/TwoEngines/AgentRocket_TwoEngines_Emitter.h"

void AgentRocket_TwoEngines_Emitter::tendToDesiredAngle(float desiredAngle, float currentAngle, float & lPowerChange, float & rPowerChange)
{
	
}

AgentRocket_TwoEngines_Emitter::AgentRocket_TwoEngines_Emitter(ProblemRocket_TwoEngines * problem, BodyEmitter * body, AGENTTYPE_ROCKET_TWO type) : AgentEmitter(problem,body), castedProblem(problem), agentType(type)
{
}

void AgentRocket_TwoEngines_Emitter::live()
{
	if (this->castedProblem->getUserControlled() || !this->problem->getProblemLive())
	{
		if (this->castedBody->isSending())
			this->castedBody->stopSending();
		return;
	}

	// Getting problem data
	float x, y, lPower, rPower, angle, hSpeed, vSpeed, distanceToGround, distanceToCenterFlat, lzSize;

	this->castedProblem->getRocketPosition(x, y);
	lPower = this->castedProblem->getRocketEnginesPower()->at(0);
	rPower = this->castedProblem->getRocketEnginesPower()->at(1);
	angle = this->castedProblem->getRocketAngle();
	angle -= PROBLEMROCKET_GUI_ANGLE_OFFSET;	// Dont forget that
	this->castedProblem->getRocketSpeed(hSpeed, vSpeed);
	distanceToGround = this->castedProblem->getRocketDistanceToGround();
	distanceToCenterFlat = this->castedProblem->getRocketDistanceToLandingZoneCenter();
	lzSize = this->castedProblem->getLandingZoneSize();

	// Variables
	float desiredAngle = 0;
	float desiredLPower = 0;
	float desiredRPower = 0;
	float temp = 0;

	float amplitude;
	float frequency;
	bool ceaseTransmission = false;

	if (this->agentType == AGENTTYPE_ROCKET_TWO::ROCKET_TWO_DIRECTION)
	{
		desiredLPower = 49;
		desiredRPower = 49;

		float dirVar = convertToRange(abs(distanceToCenterFlat),
			0.0f,
			abs(abs(distanceToCenterFlat) - lzSize/2),
			0.0f,
			this->castedProblem->getPowerMax() / 2);

		// Need to go right
		if (distanceToCenterFlat < 0.0f)
		{
			desiredLPower -= dirVar;
			desiredRPower += dirVar;
		}
		else if (distanceToCenterFlat > 0.0f)
		{
			desiredLPower += dirVar;
			desiredRPower -= dirVar;
		}

	}
	// The stabilizer wants to keep the rocket at angle 0
	else if (this->agentType == AGENTTYPE_ROCKET_TWO::ROCKET_TWO_STABILIZER)
	{
		desiredLPower = 49;
		desiredRPower = 49;

		// VSpeed
		float powerVariation = convertToRange(abs(vSpeed),
			0.0f,
			PROBLEMROCKET_TWO_PROBLEM_MAXVSPEED,
			0.0f,
			this->castedProblem->getPowerMax()/2);

		if (vSpeed > 0)
			powerVariation *= -1;

		desiredLPower += powerVariation;
		desiredRPower += powerVariation;

		// Rotation
		float rotationVariation = convertToRange(abs(angle),
			0.0f,
			45.0f,
			0.0f,
			this->castedProblem->getPowerMax() / 2);
		
		if (angle < 0)
		{
			desiredLPower -= rotationVariation;
			desiredRPower += rotationVariation;
		}
		else if (angle > 0)
		{
			desiredLPower += rotationVariation;
			desiredRPower -= rotationVariation;
		}

		// HSpeed
		// Rotation
		float angleVar = convertToRange(abs(hSpeed),
			0.0f,
			45.0f,
			0.0f,
			this->castedProblem->getPowerMax() / 2);

		if (hSpeed < 0)
		{
			desiredLPower += rotationVariation;
			desiredRPower -= rotationVariation;
		}
		else if (hSpeed > 0)
		{
			desiredLPower += rotationVariation;
			desiredRPower -= rotationVariation;
		}
	}

	if (ceaseTransmission)
	{
		this->castedBody->stopSending();
		return;
	}
	else
	{
		// 2 cases :

		// Sending
		// If we're using relative change, convert the desired angle to a relative angle
		if (this->castedProblem->getUseRelativeChange())
		{
			desiredLPower -= lPower;
			desiredRPower -= rPower;
		}

		//cout << "DESIRED : " << desiredLPower << ", " << desiredRPower << endl;

		desiredLPower += this->castedProblem->getPowerMax();
		amplitude = convertToRange(desiredLPower,
			0,
			this->castedProblem->getPowerMax() * 2,
			this->castedProblem->getWaveAmplitudeOffset(),
			this->castedProblem->getWaveAmplitudeRange());

		desiredRPower += this->castedProblem->getPowerMax();
		frequency = convertToRange(desiredRPower,
			0,
			this->castedProblem->getPowerMax() * 2,
			this->castedProblem->getWaveFrequencyOffset(),
			this->castedProblem->getWaveFrequencyRange());

		//cout << "SENDING : " << frequency << "," << amplitude << endl;
		this->castedBody->send(frequency, amplitude);
	}
}

bool AgentRocket_TwoEngines_Emitter::isLinked()
{
	return AgentEmitter::isLinked();
}

bool AgentRocket_TwoEngines_Emitter::isProblemLinked()
{
	return this->castedProblem != NULL;
}

void AgentRocket_TwoEngines_Emitter::setAgentType(AGENTTYPE_ROCKET_TWO type)
{
	this->agentType = type;
}

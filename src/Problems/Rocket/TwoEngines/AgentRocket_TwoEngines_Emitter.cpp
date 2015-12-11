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

	this->castedProblem->getRocketPosition(x, y);		// Rocket position
	lPower = this->castedProblem->getRocketEnginesPower()->at(0);	// Rocket current left power
	rPower = this->castedProblem->getRocketEnginesPower()->at(1);	// Rocket current right power
	angle = this->castedProblem->getRocketAngle();					// rocket current angle
	angle -= PROBLEMROCKET_GUI_ANGLE_OFFSET;	// Dont forget that
	this->castedProblem->getRocketSpeed(hSpeed, vSpeed);		// Rocket current speed
	distanceToGround = this->castedProblem->getRocketDistanceToGround();	// Rocket distance to ground
	distanceToCenterFlat = this->castedProblem->getRocketDistanceToLandingZoneCenter();	// Rocket distance to center of the landing zone
	lzSize = this->castedProblem->getLandingZoneSize();	// Landing zone size (width)
	float landingMaxHSPeed, landingMaxVSpeed, landingMaxAngle; // Correct landing specs
	this->castedProblem->getSafeLandingSpecs(landingMaxHSPeed, landingMaxVSpeed, landingMaxAngle);
	

	// Variables
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

		if (abs(distanceToCenterFlat) > lzSize / 2)
		{
			float dirVar = convertToRange(abs(distanceToCenterFlat),
				0.0f,
				abs(abs(distanceToCenterFlat) - lzSize / 2),
				0.0f,
				this->castedProblem->getPowerMax() / 2);

			float angleVar = convertToRange(abs(angle),
				0.0f,
				abs(PROBLEMROCKET_TWO_PROBLEM_MAXANGLE),
				0.0f,
				1);

			// Need to go right
			if (distanceToCenterFlat < 0.0f)
			{
				desiredLPower -= dirVar - angleVar * dirVar;
				desiredRPower += dirVar - angleVar * dirVar;
			}
			else if (distanceToCenterFlat > 0.0f)
			{
				desiredLPower += dirVar - angleVar * dirVar;
				desiredRPower -= dirVar - angleVar * dirVar;
			}
		}
		else
			ceaseTransmission = true;
		
	}
	// The stabilizer wants to keep the rocket at angle 0
	else if (this->agentType == AGENTTYPE_ROCKET_TWO::ROCKET_TWO_ALTITUDE)
	{
		// Are we in the landing zone?
		if (abs(distanceToCenterFlat) < lzSize / 2)
		{
			// If we are : descend
			float speedVar = convertToRange(abs(vSpeed),
				0.0f,
				landingMaxAngle,
				0.0f,
				this->castedProblem->getPowerMax() / 2);

			desiredLPower = speedVar;
			desiredRPower = speedVar;
		}
		else
			ceaseTransmission = true;
	}
	else if (this->agentType == AGENTTYPE_ROCKET_TWO::ROCKET_TWO_STABILIZER_ANGLE)
	{
		desiredLPower = 50.0f;
		desiredRPower = 50.0f;

		float angleVar = convertToRange(abs(angle),
			0.0f,
			PROBLEMROCKET_TWO_PROBLEM_MAXANGLE,
			0.0f,
			this->castedProblem->getPowerMax() / 2);

		if (angle < 0.0f)
		{
			desiredLPower -= angleVar;
			desiredRPower += angleVar;
		}
		else
		{
			desiredLPower += angleVar;
			desiredRPower -= angleVar;
		}
	}
	else if (this->agentType == AGENTTYPE_ROCKET_TWO::ROCKET_TWO_STABILIZER_HSPEED)
	{
		desiredLPower = 50.0f;
		desiredRPower = 50.0f;

		float hSpeedVar = convertToRange(abs(hSpeed),
			0.0f,
			PROBLEMROCKET_TWO_PROBLEM_MAXHSPEED,
			0.0f,
			this->castedProblem->getPowerMax() / 2);

		if (hSpeed < 0.0f)
		{
			desiredLPower += hSpeedVar;
			desiredRPower -= hSpeedVar;
		}
		else
		{
			desiredLPower -= hSpeedVar;
			desiredRPower += hSpeedVar;
		}
	}
	else if (this->agentType == AGENTTYPE_ROCKET_TWO::ROCKET_TWO_STABILIZER_VSPEED)
	{
		desiredLPower = 50.0f;
		desiredRPower = 50.0f;

		float vSpeedVar = convertToRange(abs(vSpeed),
			0.0f,
			PROBLEMROCKET_TWO_PROBLEM_MAXVSPEED,
			0.0f,
			this->castedProblem->getPowerMax() / 2);

		if (vSpeed < 0.0f)
		{
			desiredLPower += vSpeedVar;
			desiredRPower += vSpeedVar;
		}
		else
		{
			desiredLPower = 0.0f;
			desiredRPower = 0.0f;
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

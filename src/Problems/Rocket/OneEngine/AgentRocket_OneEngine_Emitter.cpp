#include "Problems/Rocket/OneEngine/AgentRocket_OneEngine_Emitter.h"

AgentRocket_OneEngine_Emitter::AgentRocket_OneEngine_Emitter(ProblemRocket_OneEngine * problem, BodyEmitter * body, AGENTTYPE_ROCKET_ONE type) : AgentEmitter(problem,body), castedProblem(problem), agentType(type)
{
}

void AgentRocket_OneEngine_Emitter::live()
{
	if (this->castedProblem->getUserControlled() || !this->problem->getProblemLive())
	{
		if (this->castedBody->isSending())
			this->castedBody->stopSending();
		return;
	}

	cout << "Agenttype : " << this->agentType << endl;

	// Getting problem data
	float x, y, power, angle, hSpeed, vSpeed, distanceToGround, distanceToCenterFlat, lzSize;

	this->castedProblem->getRocketPosition(x, y);
	power = this->castedProblem->getRocketEnginesPower()->at(0);
	angle = this->castedProblem->getRocketAngle();
	angle -= PROBLEMROCKET_GUI_ANGLE_OFFSET;	// Dont forget that
	this->castedProblem->getRocketSpeed(hSpeed, vSpeed);
	distanceToGround = this->castedProblem->getRocketDistanceToGround();
	distanceToCenterFlat = this->castedProblem->getRocketDistanceToLandingZoneCenter();
	lzSize = this->castedProblem->getLandingZoneSize();

	// Variables
	float desiredAngle = 0;
	float desiredPower = 0;
	float temp = 0;

	float amplitude;
	float frequency;
	
	if (this->agentType == AGENTTYPE_ROCKET_ONE::ROCKET_ONE_DIRECTION)
	{
		// Direct the rocket towards the flatzone
		desiredAngle = convertToRange(abs(distanceToCenterFlat),
			0,
			lzSize / 2,
			0,
			PROBLEMROCKET_ONE_PROBLEM_MAXANGLE);

		if (distanceToCenterFlat > 0)
			desiredAngle *= -1;
		cout << "DESIRED ANGLE " << desiredAngle << endl;
		desiredPower = 50;
	}
	else if (this->agentType == AGENTTYPE_ROCKET_ONE::ROCKET_ONE_REGULATOR)
	{
		desiredAngle = 0;

		// If we're too fast : regain control
		if (abs(hSpeed) > PROBLEMROCKET_ONE_PROBLEM_MAXHSPEED || abs(vSpeed) > PROBLEMROCKET_ONE_PROBLEM_MAXHSPEED)
		{
			if (abs(hSpeed) > PROBLEMROCKET_ONE_PROBLEM_MAXHSPEED)
			{
				desiredAngle = PROBLEMROCKET_ONE_PROBLEM_MAXANGLE;
			}
			else
			{
				desiredAngle = convertToRange(abs(hSpeed),
					0,
					PROBLEMROCKET_ONE_PROBLEM_MAXHSPEED / 2,	// That 0.5 factor makes it brake faster
					0,
					PROBLEMROCKET_ONE_PROBLEM_MAXANGLE);
			}

			if (hSpeed < 0)
				desiredAngle *= -1;

			desiredPower = 100;
		}
		// If we're above the flatzone
		else if (abs(distanceToCenterFlat) <= lzSize / 2)
		{
			// Nullify hSpeed, and start descent
			desiredAngle = convertToRange(abs(hSpeed),
				0,
				PROBLEMROCKET_ONE_PROBLEM_MAXHSPEED / 2,	// That 0.5 factor makes it brake faster
				0,
				PROBLEMROCKET_ONE_PROBLEM_MAXANGLE);

			if (hSpeed < 0)
				desiredAngle *= -1;

			temp = abs(vSpeed);
			if (vSpeed > 0)
				temp = 0;
			desiredPower = convertToRange(temp,
				0,
				PROBLEMROCKET_ONE_PROBLEM_MAXVSPEED,
				0,
				100);
		}
		else
		{
			desiredAngle = 0;
			desiredPower = 50;
		}
	}

	// Sending
	desiredAngle -= angle;
	desiredAngle += PROBLEMROCKET_ONE_PROBLEM_MAXANGLE;
	amplitude = convertToRange(desiredAngle,
		0,
		PROBLEMROCKET_ONE_PROBLEM_MAXANGLE * 2,
		this->castedProblem->getWaveAmplitudeOffset(),
		this->castedProblem->getWaveAmplitudeRange());

	desiredPower -= power;
	desiredPower += this->castedProblem->getPowerMax();
	frequency = convertToRange(desiredPower,
		0,
		this->castedProblem->getPowerMax() * 2,
		this->castedProblem->getWaveFrequencyOffset(),
		this->castedProblem->getWaveFrequencyRange());

	cout << "SENDING : " << frequency << "," << amplitude << endl;
	this->castedBody->send(frequency, amplitude);
}

bool AgentRocket_OneEngine_Emitter::isLinked()
{
	return AgentEmitter::isLinked();
}

bool AgentRocket_OneEngine_Emitter::isProblemLinked()
{
	return this->castedProblem != NULL;
}

void AgentRocket_OneEngine_Emitter::setAgentType(AGENTTYPE_ROCKET_ONE type)
{
	this->agentType = type;
}

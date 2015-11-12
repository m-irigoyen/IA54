#include "Problems/Rocket/OneEngine/AgentRocket_OneEngine_Emitter.h"

AgentRocket_OneEngine_Emitter::AgentRocket_OneEngine_Emitter(ProblemRocket_OneEngine * problem, BodyEmitter * body, PROBLEMROCKET_AGENTTYPE_ONE type) : AgentEmitter(problem,body), castedProblem(problem), agentType(type)
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

	// Getting problem data
	double x, y, power, angle, hSpeed, vSpeed, distanceToGround, distanceToCenterFlat, lzSize;

	this->castedProblem->getRocketPosition(x, y);
	power = this->castedProblem->getRocketEnginesPower()->at(0);
	angle = this->castedProblem->getRocketAngle();
	this->castedProblem->getRocketSpeed(hSpeed, vSpeed);
	distanceToGround = this->castedProblem->getRocketDistanceToGround();
	distanceToCenterFlat = this->castedProblem->getRocketDistanceToLandingZoneCenter();
	lzSize = this->castedProblem->getLandingZoneSize();

	// Variables
	double desiredAngle = 0;
	double desiredPower = 0;

	double amplitude;
	double frequency;
	
	switch (this->agentType)
	{
	case PROBLEMROCKET_AGENTTYPE_ONE::ROCKET_HS_ONE_DIRECTION:

		// Direct the rocket towards the flatzone
		if (abs(distanceToCenterFlat) >= lzSize/2)
		{
			desiredAngle = PROBLEMROCKET_ONE_PROBLEM_MAXANGLE;
			if (distanceToCenterFlat > 0)
				desiredAngle *= -1;
		}
		else
			desiredAngle = 0;

		desiredPower = 50;

		break;
	case PROBLEMROCKET_AGENTTYPE_ONE::ROCKET_HS_ONE_REGULATOR:
		
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
				desiredAngle = this->convertToRange(abs(hSpeed),
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
			if (vSpeed > 0)
				desiredPower = 0;
			else if (abs(hSpeed) < PROBLEMROCKET_ONE_PROBLEM_MAXHSPEED / 2 || abs(vSpeed) > PROBLEMROCKET_ONE_PROBLEM_MAXVSPEED)
				desiredPower = 75;
			else
				desiredPower = 25;
				

			desiredAngle = this->convertToRange(abs(hSpeed),
						0,
						PROBLEMROCKET_ONE_PROBLEM_MAXHSPEED / 2,	// That 0.5 factor makes it brake faster
						0,
						PROBLEMROCKET_ONE_PROBLEM_MAXANGLE);


		}
		else
		{
			desiredAngle = 0;
			desiredPower = 50;
		}
		break;
	}

	// Sending
	amplitude = this->convertToRange(desiredAngle + PROBLEMROCKET_ONE_PROBLEM_MAXANGLE,
		0,
		PROBLEMROCKET_ONE_PROBLEM_MAXANGLE * 2,
		this->castedProblem->getWaveAmplitudeOffset(),
		this->castedProblem->getWaveAmplitudeRange());

	frequency = this->convertToRange(desiredPower,
		0,
		this->castedProblem->getPowerMax(),
		this->castedProblem->getWaveFrequencyOffset(),
		this->castedProblem->getWaveFrequencyRange());

	//cout << "SENDING : " << frequency << "," << amplitude << endl;
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

void AgentRocket_OneEngine_Emitter::setAgentType(PROBLEMROCKET_AGENTTYPE_ONE type)
{
	this->agentType = type;
}

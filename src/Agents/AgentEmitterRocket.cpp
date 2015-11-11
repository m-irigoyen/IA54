#include "AgentEmitterRocket.h"

AgentEmitterRocket::AgentEmitterRocket(ProblemRocket * problem, BodyEmitter * body, AGENTTYPE_ROCKET type) : AgentEmitter(problem,body), castedProblem(problem), agentType(type)
{
}

void AgentEmitterRocket::live()
{
	if (!this->problem->getProblemLive())
	{
		if (this->castedBody->isSending())
			this->castedBody->stopSending();
		return;
	}

	// Getting problem data
	double x, y, power, angle, hSpeed, vSpeed, distanceToGround, distanceToCenterFlat;
	this->castedProblem->getProblemData(x, y, hSpeed, vSpeed, angle, power, distanceToGround, distanceToCenterFlat);

	double desiredAngle = 0;
	double desiredPower = 0;
	double temp;

	double amplitude;
	double frequency;
	
	switch (this->agentType)
	{
	case AGENTTYPE_ROCKET::ROCKET_DIRECTION :
		// We send the distance to flat zone. This is converted to amplitude : positive amplitude means towards right

		// -maxDist		dist	maxDist
		// -maxAngle	angle	maxAngle

		if (distanceToCenterFlat >= ROCKET_PROBLEM_MAXDISTANCE)
		{
			// Positive max angle
			desiredAngle = ROCKET_PROBLEM_MAXANGLE;
		}
		else if (distanceToCenterFlat <= -ROCKET_PROBLEM_MAXDISTANCE)
		{
			// Negative max angle
			desiredAngle = -ROCKET_PROBLEM_MAXANGLE;
		}
		else
		{
			// Compute angle
			desiredAngle = 0;
		}

		desiredPower = 50;
			// Power = half

		break;
	case AGENTTYPE_ROCKET::ROCKET_REGULATOR:

		
		desiredAngle = 0;
		
		if (hSpeed > ROCKET_PROBLEM_MAXHSPEED || hSpeed < -ROCKET_PROBLEM_MAXHSPEED)
		{
			temp = abs(hSpeed);
			desiredAngle = this->convertToRange(hSpeed,
				0,
				ROCKET_PROBLEM_MAXHSPEED,
				0,
				ROCKET_PROBLEM_MAXANGLE);

			if (hSpeed < 0)
				desiredAngle *= -1;

			desiredPower = 100;
		}
		// We're in the landing area : slow down to a halt on hSpeed, and begin descent
		else if (distanceToCenterFlat > -ROCKET_PROBLEM_MAXDISTANCE && x < ROCKET_PROBLEM_MAXDISTANCE)
		{
			// Nullify hSpeed
			temp = abs(hSpeed);
			desiredAngle = this->convertToRange(temp,
				0,
				ROCKET_PROBLEM_MAXHSPEED,
				0,
				ROCKET_PROBLEM_MAXANGLE);

			if (hSpeed < 0)
				desiredAngle *= -1;
			
			// Start dropping 
			if (vSpeed < ROCKET_PROBLEM_MAXVSPEED / 2)
			{
				desiredPower = 75;
			}
			else
			{
				desiredPower = 0;
			}
		}
		else
		{
			desiredAngle = 0;
			desiredPower = 50;
		}
		break;
	}

	// Sending
	amplitude = this->convertToRange(desiredAngle + ROCKET_PROBLEM_MAXANGLE,
		0,
		ROCKET_PROBLEM_MAXANGLE * 2,
		ROCKET_WAVE_AMPLITUDE_OFFSET,
		ROCKET_WAVE_AMPLITUDE_RANGE);

	frequency = this->convertToRange(desiredPower,
		0,
		ROCKET_SPECS_POWER_MAX,
		ROCKET_WAVE_FREQUENCY_OFFSET,
		ROCKET_WAVE_FREQUENCY_RANGE);

	//cout << "SENDING : " << frequency << "," << amplitude << endl;
	this->castedBody->send(frequency, amplitude);
}

bool AgentEmitterRocket::isLinked()
{
	return AgentEmitter::isLinked();
}

bool AgentEmitterRocket::isProblemLinked()
{
	return this->castedProblem != NULL;
}

void AgentEmitterRocket::setAgentType(AGENTTYPE_ROCKET type)
{
	this->agentType = type;
}

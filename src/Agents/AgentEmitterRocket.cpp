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

	// Amplitude is direction, frequency is power
	

	double x, y, power, angle, hSpeed, vSpeed, distanceToGround, distanceToCenterFlat;
	this->castedProblem->getProblemData(x, y, hSpeed, vSpeed, angle, power, distanceToGround, distanceToCenterFlat);

	double desiredAngle;
	double tempDistance;
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
			desiredAngle = ROCKET_PROBLEM_MAXDISTANCE;
		}
		else if (distanceToCenterFlat <= ROCKET_PROBLEM_MAXDISTANCE)
		{
			// Negative max angle
			desiredAngle = -ROCKET_PROBLEM_MAXDISTANCE;
		}
		else
		{
			// Compute angle
			desiredAngle = this->convertToRange(distanceToCenterFlat + ROCKET_PROBLEM_MAXDISTANCE,
				ROCKET_PROBLEM_MAXDISTANCE * 2,
				0,
				ROCKET_PROBLEM_MAXANGLE * 2,
				0);
		}

		//desiredAngle -= ROCKET_PROBLEM_MAXANGLE;

		amplitude = this->convertToRange(desiredAngle,
			ROCKET_PROBLEM_MAXANGLE * 2,
			0,
			ROCKET_WAVE_AMPLITUDE_RANGE,
			ROCKET_WAVE_AMPLITUDE_OFFSET);

		frequency = ROCKET_WAVE_FREQUENCY_OFFSET+ROCKET_WAVE_FREQUENCY_RANGE/2;	// Power = half

		cout << "COMPUTED : " << 50 << ", " << desiredAngle - ROCKET_PROBLEM_MAXANGLE << endl;
		
		break;
	case AGENTTYPE_ROCKET::ROCKET_REGULATOR:

		// Regulate speed
		amplitude = (ROCKET_WAVE_AMPLITUDE_RANGE) / 2 + ROCKET_WAVE_AMPLITUDE_OFFSET; // Angle : 0
		frequency = (ROCKET_WAVE_FREQUENCY_RANGE) / 2 + ROCKET_WAVE_FREQUENCY_OFFSET; // Power : half
		break;
	}
	cout << "SENDING : " << frequency << "," << amplitude << endl;
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

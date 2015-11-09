#include "AgentEmitterRocket.h"

AgentEmitterRocket::AgentEmitterRocket(ProblemRocket * problem, BodyEmitter * body, AGENTTYPE_ROCKET type) : AgentEmitter(problem,body), castedProblem(problem), agentType(type)
{
}

void AgentEmitterRocket::live()
{
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
		desiredAngle;

		// Compute the angle to apply based on the distance
		tempDistance = abs(distanceToCenterFlat);
		if (tempDistance >= ROCKET_PROBLEM_MAXDISTANCE)
			desiredAngle = ROCKET_PROBLEM_MAXANGLE;
		else
			desiredAngle = (distanceToCenterFlat * ROCKET_PROBLEM_MAXANGLE) / ROCKET_PROBLEM_MAXDISTANCE;

		// Correct the sign
		if (distanceToCenterFlat < 0)
			desiredAngle *= -1;

		// Now : we need to translate that desired angle into an amplitude
		// -MAXANGLE		->		MAX ANGLE
		// 0			->			MAX AMPLITUDE - AMPLITUDE OFFSET
		// Gives
		// 0		->		MAX ANGLE+MAX ANGLE
		// 0			->			MAX AMPLITUDE - AMPLITUDE OFFSET

		// ( (desiredAngle + MAX_ANGLE) * (MAX_AMP - AMP_OFFSET)	/ (MAX_ANGLE+MAX_ANGLE

		amplitude = ((desiredAngle + ROCKET_PROBLEM_MAXANGLE) * ROCKET_WAVE_AMPLITUDE_RANGE) / (ROCKET_PROBLEM_MAXANGLE * 2);
		amplitude += ROCKET_WAVE_AMPLITUDE_OFFSET;		// Adding the offset back : we don't want 0 in amplitude

		frequency = ROCKET_WAVE_FREQUENCY_OFFSET;	// Power = 0
		break;
	case AGENTTYPE_ROCKET::ROCKET_ALTITUDE:
		amplitude = (ROCKET_WAVE_AMPLITUDE_RANGE) / 2 + ROCKET_WAVE_AMPLITUDE_OFFSET; // Angle : 0
		frequency = (ROCKET_WAVE_FREQUENCY_RANGE) / 2 + ROCKET_WAVE_FREQUENCY_OFFSET; // Power : half
		break;
	}
	this->castedBody->send(amplitude, frequency);
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

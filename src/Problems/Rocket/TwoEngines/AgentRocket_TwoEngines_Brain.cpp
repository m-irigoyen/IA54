#include "Problems/Rocket/TwoEngines/AgentRocket_TwoEngines_Brain.h"

AgentRocket_TwoEngines_Brain::AgentRocket_TwoEngines_Brain(ProblemRocket_TwoEngines * problem, bool active) : AgentRocket_Brain(problem,active), castedProblem(problem)
{
}

void AgentRocket_TwoEngines_Brain::live()
{
	if (this->castedProblem->getUserControlled() || !this->problem->getProblemLive())
		return;

	map<int, int>& agentCount = this->castedProblem->getAgentCount();

	this->clearDesiredState();

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
	float landingMaxHSPeed, landingMaxVSpeed, landingMaxAngle; // Correct landing specs
	this->castedProblem->getSafeLandingSpecs(landingMaxHSPeed, landingMaxVSpeed, landingMaxAngle);

	float highestPointX, highestPointY;
	this->castedProblem->getTerrain()->getHighestPointBeforeLandingZone(x, y, highestPointX, highestPointY);
	this->castedProblem->setDesiredAltitude(highestPointY + PROBLEMROCKET_ALTITUDE_OFFSET);


	// Decision making
	if (x > this->castedProblem->getTerrain()->getWidth() - 100.0f
		|| x < 100.0f)
	{
		// We're too close to the world's edge : stabilize, and get away
		this->desiredState.at((int)AGENTTYPE_ROCKET_TWO::ROCKET_TWO_DIRECTION) = 1;
		this->desiredState.at((int)AGENTTYPE_ROCKET_TWO::ROCKET_TWO_STABILIZER_ANGLE) = 1;
		this->desiredState.at((int)AGENTTYPE_ROCKET_TWO::ROCKET_TWO_STABILIZER_VSPEED) = 1;
		this->desiredState.at((int)AGENTTYPE_ROCKET_TWO::ROCKET_TWO_STABILIZER_HSPEED) = 1;
	}
	else if (abs(distanceToCenterFlat) < (lzSize / 2))
	{
		// Wer are in the landing zone : begin descent

		// Harder horizontal stabilization
		this->desiredState.at((int)AGENTTYPE_ROCKET_TWO::ROCKET_TWO_STABILIZER_HSPEED) = convertToRange(abs(hSpeed),
			0,
			this->castedProblem->getMaxHSpeed() / 2,
			1,
			4);

		// Softer vertical stabilization
		this->desiredState.at((int)AGENTTYPE_ROCKET_TWO::ROCKET_TWO_STABILIZER_VSPEED) = convertToRange(abs(vSpeed),
			0,
			this->castedProblem->getMaxVSpeed(),
			1,
			3);

		// Harder angle stabilization
		this->desiredState.at((int)AGENTTYPE_ROCKET_TWO::ROCKET_TWO_STABILIZER_ANGLE) = convertToRange(abs(angle),
			0,
			this->castedProblem->getMaxAngle() / 2,
			1,
			4);

		// If landing values are correct, start the descent
		if (this->castedProblem->checkCorrectLanding(x, y, hSpeed*2, vSpeed*2, angle*2))
		{
			// Descent
			this->desiredState.at((int)AGENTTYPE_ROCKET_TWO::ROCKET_TWO_ALTITUDE) = convertToRange(abs(distanceToGround),
				0,
				500,
				1,
				4);

			// Direction
			this->desiredState.at((int)AGENTTYPE_ROCKET_TWO::ROCKET_TWO_DIRECTION) = convertToRange(abs(distanceToCenterFlat),
				0,
				lzSize/2,
				0,
				3);
		}
		else
		{
			this->desiredState.at((int)AGENTTYPE_ROCKET_TWO::ROCKET_TWO_DIRECTION) = 0;
			this->desiredState.at((int)AGENTTYPE_ROCKET_TWO::ROCKET_TWO_ALTITUDE) = 0;
		}
	}
	else
	{
		// We're not above the landing zone
		// We need to stabilize in vertical and horizontal speed first

		// Stabilizing hspeed
		this->desiredState.at((int)AGENTTYPE_ROCKET_TWO::ROCKET_TWO_STABILIZER_HSPEED) = convertToRange(abs(hSpeed),
			0,
			this->castedProblem->getMaxHSpeed(),
			1,
			3);

		// Stabilizing vspeed
		if (vSpeed < 0.0f)
		{
			this->desiredState.at((int)AGENTTYPE_ROCKET_TWO::ROCKET_TWO_STABILIZER_VSPEED) = convertToRange(abs(vSpeed),
				0,
				this->castedProblem->getMaxVSpeed(),
				1,
				3);
		}
		else
		{
			this->desiredState.at((int)AGENTTYPE_ROCKET_TWO::ROCKET_TWO_STABILIZER_VSPEED) = convertToRange(abs(vSpeed),
				0,
				this->castedProblem->getMaxVSpeed()/2,
				1,
				3);
		}

		// prioritize horizontal and vertical stabilization
		if (hSpeed > landingMaxHSPeed
			|| vSpeed > landingMaxVSpeed)
			return;

		// then, stabilize angle
		this->desiredState.at((int)AGENTTYPE_ROCKET_TWO::ROCKET_TWO_STABILIZER_ANGLE) = convertToRange(abs(angle),
			0,
			PROBLEMROCKET_CRUISE_MAXANGLE,
			1,
			4);

		if (y > highestPointY + PROBLEMROCKET_ALTITUDE_OFFSET)
		{
			// Direction : stabilize before caring about direction
			if (this->desiredState.at((int)AGENTTYPE_ROCKET_TWO::ROCKET_TWO_STABILIZER_VSPEED) > 2
				|| this->desiredState.at((int)AGENTTYPE_ROCKET_TWO::ROCKET_TWO_STABILIZER_HSPEED) > 2
				|| this->desiredState.at((int)AGENTTYPE_ROCKET_TWO::ROCKET_TWO_STABILIZER_ANGLE) > 2)
				this->desiredState.at((int)AGENTTYPE_ROCKET_TWO::ROCKET_TWO_DIRECTION) = 0;
			else
				this->desiredState.at((int)AGENTTYPE_ROCKET_TWO::ROCKET_TWO_DIRECTION) = 1;

			this->desiredState.at((int)AGENTTYPE_ROCKET_TWO::ROCKET_TWO_ALTITUDE) = 0;
		}
		else
		{
			this->desiredState.at((int)AGENTTYPE_ROCKET_TWO::ROCKET_TWO_ALTITUDE) = 1;
		}
	}
}

bool AgentRocket_TwoEngines_Brain::isProblemLinked()
{
	if (this->castedProblem != NULL)
		return true;
	else
		return false;
}

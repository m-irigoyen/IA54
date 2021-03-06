#include "Problems/Rocket/OneEngine/AgentRocket_OneEngine_Brain.h"

AgentRocket_OneEngine_Brain::AgentRocket_OneEngine_Brain(ProblemRocket_OneEngine * problem, bool active) : AgentRocket_Brain(problem, active), castedProblem(problem)
{
}

void AgentRocket_OneEngine_Brain::live()
{
	if (this->castedProblem->getUserControlled() || !this->problem->getProblemLive())
		return;

	map<int, int>& agentCount = this->castedProblem->getAgentCount();

	this->clearDesiredState();

	// Getting problem data
	float x, y, power, angle, hSpeed, vSpeed, distanceToGround, distanceToCenterFlat, lzSize, closestTerrainX, closestTerrainY, closestTerrainDistance;

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
	
	// Setting desired altitude
	float highestPointX, highestPointY;
	this->castedProblem->getTerrain()->getHighestPointBeforeLandingZone(x, y, highestPointX, highestPointY);
	this->castedProblem->setDesiredAltitude(highestPointY + PROBLEMROCKET_ALTITUDE_OFFSET + 50.0f); // Forced to add that to avoid certain problems in plateau level
	this->castedProblem->getTerrain()->getClosestPointFromRocket(x, y, closestTerrainX, closestTerrainY, closestTerrainDistance);


		// Decision making
	if (x > this->castedProblem->getTerrain()->getWidth() - 100.0f
		|| x < 100.0f)
	{
		// We're too close to the world's edge : stabilize, and get away
		this->desiredState.at((int)AGENTTYPE_ROCKET_ONE::ROCKET_ONE_DIRECTION) = 1;
		this->desiredState.at((int)AGENTTYPE_ROCKET_ONE::ROCKET_ONE_STABILIZER_VSPEED) = 1;
		this->desiredState.at((int)AGENTTYPE_ROCKET_ONE::ROCKET_ONE_STABILIZER_HSPEED) = 1;
		this->desiredState.at((int)AGENTTYPE_ROCKET_ONE::ROCKET_ONE_AVOIDER) = 1;
	}
	else if (abs(distanceToCenterFlat) < (lzSize / 2))
	{
		// We are above the landing zone
		// Harder horizontal stabilization
		this->desiredState.at((int)AGENTTYPE_ROCKET_ONE::ROCKET_ONE_STABILIZER_HSPEED) = (int)round(convertToRange(abs(hSpeed),
			0.0f,
			this->castedProblem->getMaxHSpeed() / 2.0f,
			1.0f,
			4.0f));

		// Softer vertical stabilization
		if (vSpeed < 0.0f)
		{
			this->desiredState.at((int)AGENTTYPE_ROCKET_ONE::ROCKET_ONE_STABILIZER_VSPEED) = (int)round(convertToRange(abs(vSpeed),
				0.0f,
				(float)this->castedProblem->getMaxVSpeed(),
				1.0f,
				3.0f));
		}
		else
			this->desiredState.at((int)AGENTTYPE_ROCKET_ONE::ROCKET_ONE_STABILIZER_VSPEED) = 1;

		if (abs(closestTerrainDistance) < 25.0f)
			this->desiredState.at((int)AGENTTYPE_ROCKET_ONE::ROCKET_ONE_AVOIDER) = 3;
		else if (abs(closestTerrainDistance) < 50.0f)
			this->desiredState.at((int)AGENTTYPE_ROCKET_ONE::ROCKET_ONE_AVOIDER) = 2;
		else
			this->desiredState.at((int)AGENTTYPE_ROCKET_ONE::ROCKET_ONE_AVOIDER) = 1;

		// Emergency landing : landing values are incorrect and we are too close from the ground
		if (!this->castedProblem->checkCorrectLanding(x, y, hSpeed * 2, vSpeed * 2, angle * 2) && distanceToGround < 100.0f)
		{
			this->desiredState.at((int)AGENTTYPE_ROCKET_ONE::ROCKET_ONE_STABILIZER_ANGLE) = 5;
			this->desiredState.at((int)AGENTTYPE_ROCKET_ONE::ROCKET_ONE_STABILIZER_HSPEED) = 1;
			this->desiredState.at((int)AGENTTYPE_ROCKET_ONE::ROCKET_ONE_STABILIZER_VSPEED) = 1;
			this->desiredState.at((int)AGENTTYPE_ROCKET_ONE::ROCKET_ONE_ALTITUDE) = 1;
			this->desiredState.at((int)AGENTTYPE_ROCKET_ONE::ROCKET_ONE_DIRECTION) = 0;
			this->desiredState.at((int)AGENTTYPE_ROCKET_ONE::ROCKET_ONE_AVOIDER) = 0;
		}
		else if (this->castedProblem->checkCorrectLanding(x, y, hSpeed * 2, vSpeed * 2, angle * 2))
		{
			// Keeping one direction agent
			this->desiredState.at((int)AGENTTYPE_ROCKET_ONE::ROCKET_ONE_DIRECTION) = 1;

			// Descent
			this->desiredState.at((int)AGENTTYPE_ROCKET_ONE::ROCKET_ONE_ALTITUDE) = (int)round(convertToRange(abs(vSpeed),
				0.0f,
				this->castedProblem->getMaxVSpeed(),
				1.0f,
				5.0f));
			this->desiredState.at((int)AGENTTYPE_ROCKET_ONE::ROCKET_ONE_ALTITUDE) = 6 - this->desiredState.at((int)AGENTTYPE_ROCKET_ONE::ROCKET_ONE_ALTITUDE);
		}
	}
	else
	{
		// We're not above the landing zone
		// We need to stabilize in vertical and horizontal speed first
		this->desiredState.at((int)AGENTTYPE_ROCKET_ONE::ROCKET_ONE_STABILIZER_HSPEED) = (int)round(convertToRange(abs(hSpeed),
			0.0f,
			this->castedProblem->getMaxHSpeed(),
			1.0f,
			6.0f));

		// Vertical stabilization
		if (vSpeed < 0.0f)
		{
			this->desiredState.at((int)AGENTTYPE_ROCKET_ONE::ROCKET_ONE_STABILIZER_VSPEED) = (int)round(convertToRange(abs(vSpeed),
				0.0f,
				this->castedProblem->getMaxVSpeed(),
				1.0f,
				3.0f));
		}
		else
			this->desiredState.at((int)AGENTTYPE_ROCKET_ONE::ROCKET_ONE_STABILIZER_VSPEED) = 3; /*(int)round(convertToRange(abs(vSpeed),
				0.0f,
				this->castedProblem->getMaxVSpeed(),
				1.0f,
				5.0f));*/

			this->desiredState.at((int)AGENTTYPE_ROCKET_ONE::ROCKET_ONE_AVOIDER) = convertToRange(100 - abs(closestTerrainDistance),
				0,
				100,
				1,
				3);
		

		// Check for altitude 
		if (y > highestPointY + PROBLEMROCKET_ALTITUDE_OFFSET)
		{
				this->desiredState.at((int)AGENTTYPE_ROCKET_ONE::ROCKET_ONE_DIRECTION) = 1;
		}
		else
		{
			if (vSpeed < 0.0f)
			{
				this->desiredState.at((int)AGENTTYPE_ROCKET_ONE::ROCKET_ONE_ALTITUDE) = (int)round(convertToRange(abs(vSpeed),
					0.0f,
					this->castedProblem->getMaxVSpeed(),
					1.0f,
					4.0f));
			}
			else
			{
				this->desiredState.at((int)AGENTTYPE_ROCKET_ONE::ROCKET_ONE_ALTITUDE) = 1;
			}
				

			this->desiredState.at((int)AGENTTYPE_ROCKET_ONE::ROCKET_ONE_DIRECTION) = 1;
		}
	}
}

bool AgentRocket_OneEngine_Brain::isProblemLinked()
{
	if (this->castedProblem != NULL)
		return true;
	else
		return false;
}

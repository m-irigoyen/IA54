#include "Problems/Rocket/OneEngine/AgentRocket_OneEngine_Emitter.h"

AgentRocket_OneEngine_Emitter::AgentRocket_OneEngine_Emitter(ProblemRocket_OneEngine * problem, BodyEmitter * body, AGENTTYPE_ROCKET_ONE type) : AgentEmitter(problem,body, (int)type), castedProblem(problem)
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
	float x, y, power, angle, hSpeed, vSpeed, distanceToGround, distanceToCenterFlat, lzSize, worldWidth, worldHeight, closestTerrainX, closestTerrainY, closestTerrainDistance;

	this->castedProblem->getTerrain()->getTerrainDimensions(worldWidth, worldHeight);
	this->castedProblem->getRocketPosition(x, y);
	power = this->castedProblem->getRocketEnginesPower()->at(0);
	angle = this->castedProblem->getRocketAngle();
	angle -= PROBLEMROCKET_GUI_ANGLE_OFFSET;	// Dont forget that
	this->castedProblem->getRocketSpeed(hSpeed, vSpeed);
	distanceToGround = this->castedProblem->getRocketDistanceToGround();
	distanceToCenterFlat = this->castedProblem->getRocketDistanceToLandingZoneCenter();
	lzSize = this->castedProblem->getLandingZoneSize();

	closestTerrainX = 0;
	closestTerrainY = 0;
	closestTerrainDistance = 10000;
	this->castedProblem->getTerrain()->getClosestPointFromRocket(x, y, closestTerrainX, closestTerrainY, closestTerrainDistance);


	// Variables
	float desiredAngle = 0;
	float desiredPower = 0;
	float temp = 0;

	float amplitude;
	float frequency;
	bool ceaseTransmission = false;
	
	if ((AGENTTYPE_ROCKET_ONE)this->getType() == AGENTTYPE_ROCKET_ONE::ROCKET_ONE_DIRECTION)
	{
		desiredPower = PROBLEMROCKET_ROCKET_POWER_BASE + this->castedProblem->getPowerOffset();

		if (abs(distanceToCenterFlat) > (lzSize / 2))
		{
			// Direct the rocket towards the flatzone
			desiredAngle = convertToRange(abs(distanceToCenterFlat),
				lzSize/2,												
				worldWidth,
				PROBLEMROCKET_CRUISE_MAXANGLE * PROBLEMROCKET_DIRECTION_LZAPPROACH,
				PROBLEMROCKET_CRUISE_MAXANGLE);

			if (distanceToCenterFlat > 0)
				desiredAngle *= -1;
		}
		else
		{
			desiredAngle = convertToRange(abs(distanceToCenterFlat),
				0.0f,
				lzSize / 2,
				0.0f,
				PROBLEMROCKET_CRUISE_MAXANGLE * PROBLEMROCKET_DIRECTION_LZAPPROACH);
				
				if (distanceToCenterFlat > 0)
					desiredAngle *= -1;
		}
	}
	else if ((AGENTTYPE_ROCKET_ONE)this->getType() == AGENTTYPE_ROCKET_ONE::ROCKET_ONE_AVOIDER)
	{
		desiredPower = PROBLEMROCKET_ROCKET_POWER_BASE + this->castedProblem->getPowerOffset();
		if (abs(closestTerrainDistance) < 100.0f)
		{
			Vector direction = Vector(x - closestTerrainX, y - closestTerrainY);
 			desiredAngle = direction.getAngle() - 90;
			if (desiredAngle < -45)
				desiredAngle = -45;
			if (desiredAngle > 45)
				desiredAngle = 45;
		}
		else
			ceaseTransmission = true;
	}
	else if ((AGENTTYPE_ROCKET_ONE)this->getType() == AGENTTYPE_ROCKET_ONE::ROCKET_ONE_STABILIZER_ANGLE)
	{
		desiredPower = PROBLEMROCKET_ROCKET_POWER_BASE + this->castedProblem->getPowerOffset();
		desiredAngle = 0;
	}
	else if ((AGENTTYPE_ROCKET_ONE)this->getType() == AGENTTYPE_ROCKET_ONE::ROCKET_ONE_ALTITUDE)
	{
		// ALTITUDE STABILIZER
		if (abs(distanceToCenterFlat) < lzSize /2)
		{
			// We're in the landing zone
			
			desiredAngle = 0;

			desiredPower = convertToRange(abs(vSpeed),
				0,
				PROBLEMROCKET_LANDING_MAXVSPEED,
				0,
				this->castedProblem->getPowerMax()/2 + this->castedProblem->getPowerOffset());
		}
		else if (y < this->castedProblem->getDesiredAltitude())
		{
			// We're lower than the desired altitude : go up
			desiredAngle = 0;

			desiredPower = convertToRange(abs(y - this->castedProblem->getDesiredAltitude()),
				0,
				100,
				this->castedProblem->getPowerMax() - PROBLEMROCKET_ROCKET_POWER_BASE + this->castedProblem->getPowerOffset(),
				this->castedProblem->getPowerMax());

			desiredPower += convertToRange(abs(angle),
				0,
				PROBLEMROCKET_ROCKET_ANGLE_TILT,
				0,
				PROBLEMROCKET_ROCKET_POWER_BASE);

			if (vSpeed > 0.0f)
				desiredPower -= convertToRange(abs(vSpeed),
					0,
					this->castedProblem->getMaxVSpeed(),
					0,
					PROBLEMROCKET_ROCKET_POWER_BASE);
		}
		else
		{
			ceaseTransmission = true;
		}
	}
	else if ((AGENTTYPE_ROCKET_ONE)this->getType() == AGENTTYPE_ROCKET_ONE::ROCKET_ONE_STABILIZER_HSPEED)
	{
		if (abs(distanceToCenterFlat) < lzSize / 2)
		{
			desiredAngle = convertToRange(abs(hSpeed),
				0,
				PROBLEMROCKET_LANDING_MAXHSPEED,
				0,
				PROBLEMROCKET_CRUISE_MAXANGLE);
		}
		else
		{
			desiredAngle = convertToRange(abs(hSpeed),
				0,
				PROBLEMROCKET_CRUISE_MAXHSPEED,
				0,
				PROBLEMROCKET_CRUISE_MAXANGLE);
		}
		

		if (hSpeed < 0)
			desiredAngle *= -1;

		desiredPower = PROBLEMROCKET_ROCKET_POWER_BASE + this->castedProblem->getPowerOffset();
	}
	else if ((AGENTTYPE_ROCKET_ONE)this->getType() == AGENTTYPE_ROCKET_ONE::ROCKET_ONE_STABILIZER_VSPEED)
	{
		desiredAngle = 0;

		if (abs(distanceToCenterFlat) < lzSize / 2)
		{
			desiredPower = convertToRange(abs(vSpeed),
				0,
				PROBLEMROCKET_LANDING_MAXVSPEED,
				PROBLEMROCKET_ROCKET_POWER_BASE + this->castedProblem->getPowerOffset(),
				this->castedProblem->getPowerMax());

			desiredPower += convertToRange(abs(angle),
				0,
				PROBLEMROCKET_ROCKET_ANGLE_TILT ,
				0,
				this->castedProblem->getPowerMax() / 2);
		}
		else
		{
			desiredPower = convertToRange(abs(vSpeed),
				0,
				PROBLEMROCKET_CRUISE_MAXVSPEED,
				PROBLEMROCKET_ROCKET_POWER_BASE + this->castedProblem->getPowerOffset(),
				this->castedProblem->getPowerMax());

			desiredPower += convertToRange(abs(angle),
				0,
				PROBLEMROCKET_ROCKET_ANGLE_TILT,
				0,
				this->castedProblem->getPowerMax() / 2);
		}
		
		

		if (vSpeed > 0.0f)
		{
			if (y < this->castedProblem->getDesiredAltitude())
				desiredPower = this->castedProblem->getPowerMax() - desiredPower - this->castedProblem->getPowerOffset();
			else
				desiredPower = 30.0f;
		}
	}

	if (ceaseTransmission)
	{
		this->castedBody->stopSending();
		return;
	}
	else
	{
		// Sending
		// If we're using relative change, convert the desired angle to a relative angle
		if (this->castedProblem->getUseRelativeChange())
		{
			desiredAngle -= angle;
			desiredPower -= power;
		}
		
		//cout << "DESIRED : " << desiredPower << ", " << desiredAngle << endl;
		desiredAngle += PROBLEMROCKET_ROCKET_ANGLE_TILT;

		amplitude = convertToRange(desiredAngle,	
			0,										
			PROBLEMROCKET_ROCKET_ANGLE_TILT * 2,
			this->castedProblem->getWaveAmplitudeOffset(),
			this->castedProblem->getWaveAmplitudeRange());

		desiredPower += this->castedProblem->getPowerMax();
		frequency = convertToRange(desiredPower,
			0,
			this->castedProblem->getPowerMax() * 2,
			this->castedProblem->getWaveFrequencyOffset(),
			this->castedProblem->getWaveFrequencyRange());

		//cout << "SENDING : " << frequency << "," << amplitude << endl;
		this->castedBody->send(frequency, amplitude);
	}
}

bool AgentRocket_OneEngine_Emitter::isLinked()
{
	return AgentEmitter::isLinked();
}

bool AgentRocket_OneEngine_Emitter::isProblemLinked()
{
	return this->castedProblem != NULL;
}
#include "Problems/Rocket/TwoEngines/AgentRocket_TwoEngines_Emitter.h"

AgentRocket_TwoEngines_Emitter::AgentRocket_TwoEngines_Emitter(ProblemRocket_TwoEngines * problem, BodyEmitter * body, AGENTTYPE_ROCKET_TWO type) : AgentEmitter(problem,body, (int)type), castedProblem(problem)
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
	float x, y, lPower, rPower, angle, hSpeed, vSpeed, distanceToGround, distanceToCenterFlat, lzSize, worldWidth, worldHeight;

	this->castedProblem->getTerrain()->getTerrainDimensions(worldWidth, worldHeight);
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

	if ((AGENTTYPE_ROCKET_TWO)this->getType() == AGENTTYPE_ROCKET_TWO::ROCKET_TWO_DIRECTION)
	{
		desiredLPower = PROBLEMROCKET_ROCKET_POWER_BASE + this->castedProblem->getPowerOffset();
		desiredRPower = PROBLEMROCKET_ROCKET_POWER_BASE + this->castedProblem->getPowerOffset();

		// Are we too close to the world's edge?
		float dirVar, angleVar;
		if (abs(distanceToCenterFlat) < lzSize / 2)
		{
			dirVar = convertToRange(abs(distanceToCenterFlat),
				0,
				lzSize / 2,
				0,
				PROBLEMROCKET_CRUISE_MAXANGLE * PROBLEMROCKET_DIRECTION_LZAPPROACH);

			angleVar = convertToRange(abs(angle),
				0.0f,
				PROBLEMROCKET_CRUISE_MAXANGLE * PROBLEMROCKET_DIRECTION_LZAPPROACH,
				0.0f,
				1);
		}
		else
		{
			dirVar = convertToRange(abs(distanceToCenterFlat),
				lzSize/2,
				worldWidth,
				PROBLEMROCKET_CRUISE_MAXANGLE * PROBLEMROCKET_DIRECTION_LZAPPROACH,
				PROBLEMROCKET_CRUISE_MAXANGLE);

			angleVar = convertToRange(abs(angle),
				0.0f,
				PROBLEMROCKET_CRUISE_MAXANGLE * PROBLEMROCKET_DIRECTION_LZAPPROACH,
				0.0f,
				1);
		}
		
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
	else if ((AGENTTYPE_ROCKET_TWO)this->getType() == AGENTTYPE_ROCKET_TWO::ROCKET_TWO_ALTITUDE)
	{
		// The stabilizer wants to keep the rocket at angle 0
		// Are we in the landing zone?
		if (abs(distanceToCenterFlat) < lzSize / 2)
		{
			// If we are : descend
			float speedVar = convertToRange(abs(vSpeed),
				0.0f,
				this->castedProblem->getMaxVSpeed(),
				0.0f,
				PROBLEMROCKET_ROCKET_POWER_BASE  + this->castedProblem->getPowerOffset());

			desiredLPower = speedVar;
			desiredRPower = speedVar;
		}
		else if (y < this->castedProblem->getDesiredAltitude())
		{
			// We're lower than the desired altitude : go up
			desiredLPower = convertToRange(abs(y - this->castedProblem->getDesiredAltitude()),
				0,
				200,
				this->castedProblem->getPowerMax() - PROBLEMROCKET_ROCKET_POWER_BASE + this->castedProblem->getPowerOffset(),
				this->castedProblem->getPowerMax());

			desiredLPower += convertToRange(abs(angle),
				0,
				PROBLEMROCKET_ROCKET_ANGLE_TILT,
				0,
				this->castedProblem->getPowerMax() / 2);

			if (vSpeed > 0.0f)
				desiredLPower -= convertToRange(abs(vSpeed),
					0,
					this->castedProblem->getMaxVSpeed(),
					0,
					PROBLEMROCKET_ROCKET_POWER_BASE);

			desiredRPower = desiredLPower;
		}
		else
			ceaseTransmission = true;
	}
	else if ((AGENTTYPE_ROCKET_TWO)this->getType() == AGENTTYPE_ROCKET_TWO::ROCKET_TWO_STABILIZER_ANGLE)
	{
		desiredLPower = PROBLEMROCKET_ROCKET_POWER_BASE + this->castedProblem->getPowerOffset();
		desiredRPower = PROBLEMROCKET_ROCKET_POWER_BASE + this->castedProblem->getPowerOffset();

		float angleVar = convertToRange(abs(angle),
			0.0f,
			PROBLEMROCKET_ROCKET_ANGLE_TILT,
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
		desiredRPower += 1;
	}
	else if ((AGENTTYPE_ROCKET_TWO)this->getType() == AGENTTYPE_ROCKET_TWO::ROCKET_TWO_STABILIZER_HSPEED)
	{
		// On règle les réacteurs à la puissance de maintien d'altitude
		desiredLPower = PROBLEMROCKET_ROCKET_POWER_BASE + this->castedProblem->getPowerOffset();
		desiredRPower = PROBLEMROCKET_ROCKET_POWER_BASE + this->castedProblem->getPowerOffset();

		// Calcul de la variation de vitesse : on convertit la vitesse 
		// horizontale (comprise entre 0 et MaxHSpeed) en une variation
		float hSpeedVar = convertToRange(abs(hSpeed),
			0.0f,
			this->castedProblem->getMaxHSpeed(),
			0.0f,
			PROBLEMROCKET_ROCKET_POWER_BASE);

		// On applique cette variation
		if (hSpeed < 0.0f)
		{
			//hSpeed < 0.0f : la fusée va vers la gauche
			// on s'orienter donc vers la droite pour équilibrer
			desiredLPower += hSpeedVar;
			desiredRPower -= hSpeedVar;
		}
		else
		{
			// et inversement
			desiredLPower -= hSpeedVar;
			desiredRPower += hSpeedVar;
		}
	}
	else if ((AGENTTYPE_ROCKET_TWO)this->getType() == AGENTTYPE_ROCKET_TWO::ROCKET_TWO_STABILIZER_VSPEED)
	{
		desiredLPower = PROBLEMROCKET_ROCKET_POWER_BASE + this->castedProblem->getPowerOffset();
		desiredRPower = PROBLEMROCKET_ROCKET_POWER_BASE + this->castedProblem->getPowerOffset();

		float vSpeedVar = convertToRange(abs(vSpeed),
			0.0f,
			this->castedProblem->getMaxVSpeed(),
			0.0f,
			this->castedProblem->getPowerMax() / 2);

		desiredLPower += vSpeedVar;
		desiredRPower += vSpeedVar;

		if (vSpeed > 0.0f)
		{
			if (y < this->castedProblem->getDesiredAltitude())
			{
				desiredLPower = this->castedProblem->getPowerMax() - desiredLPower - this->castedProblem->getPowerOffset();
				desiredRPower = this->castedProblem->getPowerMax() - desiredRPower - this->castedProblem->getPowerOffset();
			}
			else
			{
				desiredLPower = 20.0f;
				desiredRPower = 20.0f;
			}
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

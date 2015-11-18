#include "World.h"

// Constructor
World::World(sf::Clock* clock, float worldLength, float worldHeight) : simulationClock(clock), maxWaveDistance(0.0f), optimiseWaveTravelDistance(true), waveAplitudeLoss(0.0f), useWaveAttenuation(true)
{
    this->receptors.clear();
    this->maxWorldDistance = calculateDistance(0,0, worldLength, worldHeight);
}

void World::clear()
{
	this->emitters.clear();
	this->receptors.clear();
	this->waves.clear();
}

// Toggle wave optimisation on/off. If its on, waves are removed as soon as they go farther than the biggest distance between an emitter and a receptor in the world. If its off, they are removed when they go off screen.
bool World::toggleWaveOptimisation()
{
    if (this->optimiseWaveTravelDistance)
        this->optimiseWaveTravelDistance = false;
    else
        this->optimiseWaveTravelDistance = true;

    return this->optimiseWaveTravelDistance;
}

// Returns closest body from given location
Body* World::getClosestBodyFromLocation(float x, float y, float rangeThreshold)
{
    Body* ret = NULL;
    float distance = rangeThreshold;
    float tempDistance;

	// Searching through all emitters to get the closest one
    for (std::vector<BodyEmitter*>::iterator it = this->emitters.begin(); it != this->emitters.end(); ++it)
    {
        tempDistance = calculateDistance(x,y,(*it)->GetPosition());
        if (tempDistance < distance)
        {
            distance = tempDistance;
            ret = (*it);
        }
    }

	// Searching through all receptors to get the closest one
    for (std::vector<BodyReceptor*>::iterator it = this->receptors.begin(); it != this->receptors.end(); ++it)
    {
        tempDistance = calculateDistance(x,y,(*it)->GetPosition());
        if (tempDistance < distance)
        {
            distance = tempDistance;
            ret = (*it);
        }
    }
    return ret;
}

// Creates a body with the given type
Body* World::createBody(BODY_TYPE bodyType, float xPos, float yPos)
{
    Body* body = NULL;
	BodyReceptor* tempBodyReceptor = NULL;
	BodyEmitter* tempBodyEmitter = NULL;
	//BodyHybrid* tempBodyHybrid;

	// Switching body type. For the given type : create the Body with correct tag at correct position, and add it to the list of bodies
    switch (bodyType)
    {
	case BODY_TYPE::BODY_EMITTER :
		tempBodyEmitter = new BodyEmitter(Semantic(Tags::emitter), xPos, yPos);
        break;
	case BODY_TYPE::BODY_RECEPTOR_COMPOSITION:
		tempBodyReceptor = new BodyReceptor_Composition(Semantic(Tags::receptor), xPos, yPos);
        break;
	case BODY_TYPE::BODY_RECEPTOR_FULLCOMPOSITION:
		tempBodyReceptor = new BodyReceptor_CompositionFull(Semantic(Tags::receptor), xPos, yPos);
		break;
	case BODY_TYPE::BODY_RECEPTOR_MEDIUM:
		tempBodyReceptor = new BodyReceptor_Medium(Semantic(Tags::receptor), xPos, yPos);
		break;
	case BODY_TYPE::BODY_HYBRID:
		/*tempBodyHybrid = new BodyHybrid(Semantic(Tags::hybrid), xPos, yPos);
		body = tempBodyHybrid;*/
		break;
    }


	if (tempBodyEmitter != NULL)
	{
		body = tempBodyEmitter;
		this->emitters.push_back(tempBodyEmitter);
		//cout << "PUSHED EMITTER BACK" << endl;

		// We've placed a new body : the max distance between an emitter and receptor may have changed
		updateMaxWaveDistance();
	}
	else if (tempBodyReceptor != NULL)
	{
		body = tempBodyReceptor;
		this->receptors.push_back(tempBodyReceptor);

		// We've placed a new body : the max distance between an emitter and receptor may have changed
		updateMaxWaveDistance();
	}

	return body;
}

/*
	This function create a new wave
	Return type : Wave*

	x				X position for the wave
	y				Y position for the wave
	radius			radius value for the wave
	frequency		frequency value for the wave
	speed			speed value for the wave
	amplitude		amplitude value for the wave
*/
Wave* World::createWave(float x, float y, int emitterId, float speed, float amplitude)
{
	// If speed wasn't specified, set it
	if (speed == -1.0f)
		speed = DEFAULT_PROPAGATION_SPEED;

	
	// Create a wave, add it to the list
	Wave * wave = new Wave(Semantic(Tags::wave), x, y, emitterId, speed, amplitude, this->waveAplitudeLoss, this->useWaveAttenuation);
	this->waves.push_back(wave);

	// return it
	return wave;
}

Wave* World::createWave(std::vector<float> position, int emitterId, float speed, float amplitude)
{
	return createWave(position.at(0), position.at(1), emitterId, speed, amplitude);
}

void World::removeBody(Body * body)
{
	for (vector<BodyEmitter*>::iterator it = this->emitters.begin(); it != this->emitters.end(); ++it)
	{
		if ((*it) == body)
		{
			this->emitters.erase(it);
			return;
		}
	}

	for (vector<BodyReceptor*>::iterator it = this->receptors.begin(); it != this->receptors.end(); ++it)
	{
		if ((*it) == body)
		{
			this->receptors.erase(it);
			return;
		}
	}
}

/*
Update each element contained in the world at each execution loop (based on the time not the frame)
Return : void
*/
void World::update(sf::Time elapsedTime, sf::Time currentFrameTime)
{
	this->currentFrameTime = currentFrameTime;

	// Updating every emitter : checking if wave creation is necessary
	for (std::vector<BodyEmitter*>::iterator it = this->emitters.begin();
		it != this->emitters.end();
		++it)
	{
		(*it)->update(elapsedTime);
		checkWaveCreation((*it));
	}

	//Updating waves : moving them through the wrodl, checking if they need to be destroyed
	std::vector<Wave*>::iterator it = this->waves.begin();
	while (it != this->waves.end())
	{
		(*it)->update(elapsedTime);

		// Attenuate the wave's amplitude
		if ((*it)->attenuate(elapsedTime))
		{
			// If it attenuated below 0, destroy it
			it = this->waves.erase(it);
		}
		else
		{
			// Else, check for collisions
			checkCollisionEvents((*it), elapsedTime);

			// Does this wave needs to be removed : 2 cases
			// Case 1 : wave optimization on, and the wave's radius is bigger than its maxRadius
			// Case 2 : the wave's radius has exceeded the max travel distance
			if ((optimiseWaveTravelDistance && (*it)->hasExceededMaxRadius())
				|| (*it)->getRadius() > this->maxWorldDistance)
				it = this->waves.erase(it);
			else
				++it;
		}
	}

	// updating receptors
	for (std::vector<BodyReceptor*>::iterator it = this->receptors.begin();
		it != this->receptors.end();
		++it)
	{
		// Updating and setting its perceptions
		(*it)->update(elapsedTime);
		setPerception((*it));
	}
}

void World::forceEndOfTransmission(BodyEmitter * body)
{
	// Create a new wave, and set its endOfTransmission flag
	Wave* w = createWave(body->GetPosition(), body->getId(), body->getCurrentSpeed(), 1.0f);
	w->setEndOfTransmission(true);
	w->setMaxRadius(body->getMaxRadius());

	// Drop the emitter's end of transmission flag
	body->stopSending();
	body->acknowledgeEndOfTransmission();
}

/*
For a specific receptor, look for each wave colliding with it, then set the receptor in consequences
*/
void World::setPerception(BodyReceptor* receptor)
{
	receptor->updateComputedValues(this->currentFrameTime);
}

//Getter functions
std::vector<Wave*>* World::getWaves()
{
	return &this->waves;
}

// Getter functions
std::vector<BodyEmitter*>* World::getEmitters()
{
    return &this->emitters;
}

// Getter functions
std::vector<BodyReceptor*>* World::getReceptors()
{
    return &this->receptors;
}

void World::setWaveAmplitude(float amplitudeLoss)
{
	this->waveAplitudeLoss = amplitudeLoss;
}

World::~World(void)
{
	for (std::vector<Wave*>::iterator it = this->waves.begin(); it != this->waves.end(); ++it)
	{
		delete (*it);
		*it = NULL;
	}
	for (std::vector<BodyReceptor*>::iterator it = this->receptors.begin(); it != this->receptors.end(); ++it)
	{
		delete (*it);
		*it = NULL;
	}

	for (std::vector<BodyEmitter*>::iterator it = this->emitters.begin(); it != this->emitters.end(); ++it)
	{
		delete (*it);
		*it = NULL;
	}

}

//Private
// Check if a wave collides with a receptor
void World::checkCollisionEvents(Wave* wave, sf::Time elapsedTime)
{
	// We check for receptors positionned between those min and max distances
	float minDistance = wave->getRadius() - wave->getSpeed()*elapsedTime.asSeconds();
	float maxDistance = wave->getRadius();

	float x1, xWave, y1, yWave;
	wave->GetPosition(xWave, yWave);

	// Going through all receptors
	for (std::vector<BodyReceptor*>::iterator it = this->receptors.begin();
		it != this->receptors.end();
		++it)
	{
		(*it)->GetPosition(x1, y1);
		// If the receptor is positionned between those distances
		if (distanceCheck(x1, y1, xWave, yWave, minDistance, maxDistance))	
		{
			// If the wave hasn't already collided with this receptor in a previous frame
			if (!wave->hasCollided((*it)->getId()))
			{
				float waveSpeed = wave->getSpeed();
				if (waveSpeed <= 0.0f)
				{
					waveSpeed = DEFAULT_PROPAGATION_SPEED;
					cout << "World::checkCollisionEvents : wave speed unset. Applying default" << endl;
				}

				// Get the distance between the wave and the receptor
				float distanceWaveReceptor = wave->getRadius() - calculateDistance(xWave, yWave, x1, y1);;

				// Computing the exact moment the wave hit the receptor (if it was between 2 frames)
				sf::Time displayT = this->currentFrameTime - this->calculateTimeElapsedInDistance(waveSpeed, distanceWaveReceptor);

				// 2 possibilities : either the wave is an end of transmission, either it's not.
				if (wave->isEndOfTransmission())
					(*it)->onEndOfTransmission(wave->getEmitterId(), displayT);
				else
				{
					// Telling the wave it hit that object
					wave->onCollisionEvent((*it)->getId());

					// Telling the object it was hit by that wave
					(*it)->onWaveCollision(wave->getEmitterId(), displayT, wave->getAmplitude());

					//cout << "COLLISION : " << wave->getEmitterId() << ", " << wave->getAmplitude() << endl;
				}
			}
		}
	}
}

// Check if those objects are separated by a distance within minDistance and maxDistance (included)
bool World::distanceCheck(float x1, float y1, float x2, float y2, float minDistance, float maxDistance)
{
	float distanceBetweenPoints = calculateDistance(x1, y1, x2, y2);
	if (distanceBetweenPoints > maxDistance || distanceBetweenPoints < minDistance)
		return false;
	return true;
}

// Calculate how much time a wave with given speed would take to travel the given distance
sf::Time World::calculateTimeElapsedInDistance(float speed, float distance)
{
    return sf::seconds(distance/speed);
}

// Helper function : distance between x and y
float World::calculateDistance(float x1, float y1, float x2, float y2)
{
	return sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
}

float World::calculateDistance(std::vector<float> pos1, std::vector<float> pos2)
{
	return calculateDistance(pos1.at(0), pos1.at(1), pos2.at(0), pos2.at(1));
}

float World::calculateDistance(float x1, float y1, std::vector<float> pos2)
{
    return calculateDistance(x1,y1, pos2.at(0), pos2.at(1));
}

// Calculates and sets the max wave distance
void World::updateMaxWaveDistance()
{
	float maxDistance = 0.0f;
	float tempDistance = 0.0f;
	float emitterDistance = 0.0f;

	// For each emitter
	for (std::vector<BodyEmitter*>::iterator itEmitter = this->emitters.begin();
		itEmitter != this->emitters.end();
		++itEmitter)
	{
		emitterDistance = 0.0f;
		// For each receptor
		for (std::vector<BodyReceptor*>::iterator itReceptor = this->receptors.begin(); itReceptor != this->receptors.end(); ++itReceptor)
		{
			// Get the distance between the emitter and the receptor
			tempDistance = calculateDistance((*itEmitter)->GetPosition(), (*itReceptor)->GetPosition());
			if (tempDistance > maxDistance)
				maxDistance = tempDistance;

			if (tempDistance > emitterDistance)
				emitterDistance = tempDistance;

			// Error checking. (This supposes that the distance will never be bigger than the diagonal of the world)
            if (maxDistance > this->maxWorldDistance)
                this->maxWaveDistance = this->maxWorldDistance;
		}
		(*itEmitter)->setMaxRadius(emitterDistance);	// Setting the max distance for that emitter
	}
	this->maxWaveDistance = maxDistance;
}

// Check if emitters needs to send a wave
void World::checkWaveCreation(BodyEmitter* emitter)
{

	if (emitter->getEndOfTransmission())
	{
		// Create a new wave, and set its endOfTransmission flag
		Wave* w = createWave(emitter->GetPosition(), emitter->getId(), emitter->getCurrentSpeed(), 1.0f);
		w->setEndOfTransmission(true);
		w->setMaxRadius(emitter->getMaxRadius());

		// Drop the emitter's end of transmission flag
		emitter->acknowledgeEndOfTransmission();
	}
	// If that emitter wants to send a wave
	else if (emitter->checkForSend(this->currentFrameTime))
	{
		// Create a new wave
		Wave* w = createWave(emitter->GetPosition(), emitter->getId(), emitter->getCurrentSpeed(), emitter->getCurrentAmplitude());

		w->setMaxRadius(emitter->getMaxRadius());

		// Transmission is just starting, there is no delay
		if (emitter->getStartOfTransmission())
		{
			emitter->setLastSendTime(this->currentFrameTime);
			emitter->acknowledgeStartTransmission();
		}
		
		// Transmission had started before, we need to compute the delay
		else
		{
			// Compute the delay between when the emitter wanted to send, and the current frame
			sf::Time newLastSendTime = emitter->getNextSendTime();
			sf::Time delay = this->currentFrameTime - newLastSendTime;
			//cout << "Delay " << delay.asSeconds() << endl;

			// Compensate that delay on the wave : Since it should have spawned earlier, so it should have traveled farther too.
			w->setRadius(delay.asSeconds()*w->getSpeed());

			// Update the emitter's send time
			emitter->setLastSendTime(newLastSendTime);
		}

		/*std::cout << "Creating new wave : " << std::endl;
		std::cout << "  NewSendTime  : " << newLastSendTime.asSeconds() << std::endl;
		std::cout << "  NextSendTime : " << emitter->getNextSendTime().asSeconds() << std::endl;
		std::cout << "  Delay  : " << delay.asSeconds() << std::endl;
		std::cout << "  Radius : " << delay.asSeconds()*w->getSpeed() << std::endl;*/
	}
}

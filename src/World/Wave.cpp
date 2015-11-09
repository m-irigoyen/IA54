#include "Wave.h"

//Constructor

Wave::Wave(Semantic type, float x, float y, int emitterId, float speed, float amplitude, 
	float amplitudeLossPerSecond, bool useAttenuation) : PhysicalObject(type, x, y), emitterId(emitterId), m_speed(speed),
	m_amplitude(amplitude), amplitudeLossPerSecond(amplitudeLossPerSecond), m_radius(0.0f), useAttenuation(useAttenuation)
{

}

//Getter
float Wave::getRadius()
{
	return m_radius;
}

float Wave::getSpeed()
{
	return m_speed;
}

float Wave::getAmplitude()
{
	return m_amplitude;
}

float Wave::getAmplitudeLossPerSecond()
{
	return this->amplitudeLossPerSecond;
}

int Wave::getEmitterId()
{
	return this->emitterId;
}

//Other
/*
Each loop of the physics engine, the wave increase its radius by a value corresponding to its speed and the elapsed time
return : void

elapsedTime			: int		// Time elapsed since the last loop (in ms)
*/
void Wave::update(sf::Time elapsedTime)
{
	float newRadius;
	newRadius = m_radius + m_speed * (elapsedTime.asSeconds());

	setRadius(newRadius);
}

// Returns true if wave has attenuated below 0 and needs to be destroyed
bool Wave::attenuate(sf::Time elapsedTime)
{
	if (!this->useAttenuation)
		return false;
	this->m_amplitude -= this->amplitudeLossPerSecond * elapsedTime.asSeconds() * COEFF_ATTENUATION;

	if (this->m_amplitude <= 0.0f)
		return true;

	return false;
}

void Wave::setRadius(float r)
{
	this->m_radius = r;
}


bool Wave::hasCollided(int receptorId)
{
	for (std::vector<int>::iterator it = this->collidedReceptors.begin();
		it != this->collidedReceptors.end();
		++it)
	{
		if ((*it) == receptorId)
			return true;
	}
	return false;
}

void Wave::onCollisionEvent(int receptorId)
{
	if (!hasCollided(receptorId))
	{
		this->collidedReceptors.push_back(receptorId);
	}
}
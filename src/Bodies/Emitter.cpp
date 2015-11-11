#include "Bodies/Emitter.h"


Emitter::Emitter() : sending(false), currentAmplitude(-1.0f), currentFrequency(-1.0f), currentSpeed(-1.0f)
{
	this->lastSendTime = sf::Time::Zero;
}


void Emitter::send(double frequency, double amplitude, double speed)
{
	if (frequency <= 0.0f || amplitude <= 0.0f)
		return;	//Can't have negative values

	if(!sending)
	{
		this->sending = true;
	}
	this->currentAmplitude = amplitude;
	this->currentFrequency = frequency;
	this->currentSpeed = speed;
}

/**
*	Call that function inside the update function of a body.
*	This will check if the emitter is sending, and if it is, if a new peak needs to be sent.
*/
bool Emitter::checkForSend(sf::Time currentTime)
{
	if (this->sending)
	{
		// If time was zero, just send already
		if (this->lastSendTime == sf::Time::Zero)
			return true;

		// Else check if new send is needed
		sf::Time check = currentTime - this->lastSendTime;
		if (check >= getTimeFromFrequency(this->currentFrequency))
		{
			return true;
		}
	}
	return false;
}

bool Emitter::isSending()
{
	return this->sending;
}

void Emitter::stopSending()
{
	if (this->sending)
	{
		this->currentAmplitude = -1.0f;
		this->currentFrequency = -1.0f;
		this->currentSpeed = -1.0f;
		this->sending = false;
		this->lastSendTime = sf::Time::Zero;
	}
}

// Setters
void Emitter::setLastSendTime(sf::Time newLastSendTime)
{
	this->lastSendTime = newLastSendTime;
}

// Getters
sf::Time Emitter::getLastSendTime()
{
	return this->lastSendTime;
}

sf::Time Emitter::getNextSendTime()
{
    //sf::Time t = sf::seconds(this->lastSendTime.asSeconds() + (1/this->currentFrequency));
    return getTimeFromFrequency(this->currentFrequency) + this->lastSendTime;
}

float Emitter::getCurrentAmplitude()
{
	return this->currentAmplitude;
}

float Emitter::getCurrentFrequency()
{
	return this->currentFrequency;
}

float Emitter::getCurrentSpeed()
{
	return this->currentSpeed;
}

// Static functions
sf::Time Emitter::getTimeFromFrequency(float frequency)
{
	sf::Time t = sf::seconds(1);
	return t / frequency;
}

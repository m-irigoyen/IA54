#ifndef EMITTER_H_
#define EMITTER_H_

// This is the interface for all emitter objects
/*
*	Emitters can send waves in the world.
*/

#include <iostream>
#include <SFML/System/Clock.hpp>

class Emitter
{
private:
	sf::Time lastSendTime;	// Last time a wave was sent
	bool sending;			// Is currently broadcasting

	float currentAmplitude;	// Amplitude
	float currentFrequency;	// Frequency in hertz
	float currentSpeed;		// Speed of the waves to be sent in meters/second

public:
	Emitter();

	virtual void initialise() = 0;	// Perform initialisation specific tasks
	virtual void send(double frequency, double amplitude, double speed = -1.0f);	// Send a wave

	/**
	*	This will check if the emitter is sending, and if it is, if a new peak needs to be sent.
	*/
	virtual bool checkForSend(sf::Time currentTime);

	virtual bool isSending();
	virtual void stopSending();	// Stop emission

	// Setters
	void setLastSendTime(sf::Time newLastSendTime);	// When newest peak has ben sent, the world will call this to notify the Emitter

	// Getters
	virtual sf::Time getLastSendTime();
	virtual sf::Time getNextSendTime();
	virtual float getCurrentAmplitude();
	virtual float getCurrentFrequency();
	virtual float getCurrentSpeed();

	// Static functions
	// TODO : Comment this
	static sf::Time getTimeFromFrequency(float frequency);
};

#endif

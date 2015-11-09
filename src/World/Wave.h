#ifndef WAVE_H_
#define WAVE_H_

#include <iostream>
#include <vector>

#include "PhysicalObject.h"

/*
	Waves are the class representing a spike of a wave.
	Each wave object represents one spike of an emitted wave.
	Each wave carries information about its amplitude : the amplitude of the spike. When receptors recieve a wave, they will remember the time they received the wave, and compute the frequency themselves by comparing the time of the next spike they receive.
	So the wave does not carry information about its frequency.
*/

#define COEFF_ATTENUATION 1

using namespace std;

class Wave : public PhysicalObject
{
public :
	//Constructor
	Wave(Semantic type, float x, float y, int emitterId, float speed, float amplitude, float ampLossPerSec = 35.0f);

	//Getter
	float getAmplitude();
	float getAmplitudeLossPerSecond();
	float getSpeed();
	float getRadius();
	int getEmitterId();
	
	void setRadius(float r);	// Update radius

	//Other
	void update(sf::Time elapsedTime);	// Update the wave : distance travelled in the given time, and attenuation
	bool attenuate(sf::Time elapsedTime);	// Returns true if wave has attenuated below 0 and needs to be destroyed
	
	bool hasCollided(int receptorId);	// Has this wave collided with that receptor
	void onCollisionEvent(int receptorId);	// Called when a wave collides with a receptor

private :
	float m_radius;			// The radius of the wave from its point of origin
	const float m_speed;	// The speed at which the wave travels
	float m_amplitude;		// The amplitude of the wave
	const int emitterId;	// The id of the Emitter body ho sent that wave

	float amplitudeLossPerSecond;	// How much amplitude is lost per second of travel

	std::vector<int> collidedReceptors;	// All the receptors this wave has hit
};

#endif
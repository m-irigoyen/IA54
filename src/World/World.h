#ifndef WORLD_H_
#define WORLD_H_

#include <vector>
#include <iostream>
#include <math.h>

#include "Bodies/BodyReceptor_Composition.h"
#include "Bodies/BodyReceptor_CompositionFull.h"
#include "Bodies/BodyReceptor_Medium.h"
#include "Bodies/BodyEmitter.h"
#include "Bodies/BodyHybrid.h"
#include "World/Wave.h"


#define DEFAULT_PROPAGATION_SPEED 100.0f
#define WORLD_WIDTH 400.0f
#define WORLD_HEIGHT 400.0f

/*
*   The World is the environment. It contains a list of all the PhysicalObjects that exist in it.
*	Each of those objects are updated every frame, in order.
*	Each update, the world checks emitters and creates a new wave if it needs to. It also sets perceptions for the objects
*/

enum BODY_TYPE	// The types of bodies that exist in the world
{
    BODY_EMITTER = 0,
	BODY_RECEPTOR_COMPOSITION,
	BODY_RECEPTOR_FULLCOMPOSITION,
	BODY_RECEPTOR_MEDIUM,
	BODY_HYBRID	// Currently unsupported.
};

class World
{
private:
	// propagation speed
	int waveSpeed;

	std::vector<Wave*> waves;	// TODO : (optimisation) Change that to a deque 
	std::vector<BodyReceptor*> receptors;
	std::vector<BodyEmitter*> emitters;

	float waveAplitudeLoss;
	bool useWaveAttenuation;

    bool optimiseWaveTravelDistance;

	float maxWaveDistance;	// Biggest distance in the world between an emitter and receptor. Passed that distance, all waves are destroyed
	float maxWorldDistance; // If above variable isn't used, this one will be

	sf::Clock* simulationClock;	// Pointer to the clock
	sf::Time currentFrameTime;	// Current frame

	// HELPER FUNCTIONS
	void checkCollisionEvents(Wave* wave, sf::Time elapsedTime);	// Check if a wave collides with a receptor
	void checkWaveCreation(BodyEmitter* emitter);	// Check if emitters needs to send a wave
	bool distanceCheck(float x1, float y1, float x2, float y2, float minDistance, float maxDistance);	// Check if a wave has gone too far

    sf::Time calculateTimeElapsedInDistance(float speed, float distance);	// Calculate how much time a wave with given speed would take to travel the given distance

	float calculateDistance(float x1, float y1, float x2, float y2);	// Helper function : distance between x and y
	float calculateDistance(std::vector<float> pos1, std::vector<float> pos2);	// Override of the above function
	float calculateDistance(float x1, float y1, std::vector<float> pos2);	// Override of the above function

public:
	World(sf::Clock* clock, float worldLength, float worldHeight);

	void clear();	// Clears the world of all waves, emitters, receptors

	void updateMaxWaveDistance();	// Calculates and sets the max wave distance
	bool toggleWaveOptimisation();	// Toggle wave optimisation on/off. If its on, waves are removed as soon as they go farther than the biggest distance between an emitter and a receptor in the world. If its off, they are removed when they go off screen.

	Body* getClosestBodyFromLocation(float x, float y, float rangeTreshold);	// Returns closest body from given location

    // Creates a body with the given type
	Body* createBody(BODY_TYPE bodyType, float xPos, float yPos);
	// Wave creation function
	Wave* createWave(float x, float y, int emitterId, float speed, float amplitude);
	Wave* createWave(std::vector<float> position, int emitterId, float speed, float amplitude);
	void removeBody(Body* body);

	// Update the world : emitters, receptors, waves
	void update(sf::Time elapsedTime, sf::Time currentFrameTime);
	void forceEndOfTransmission(BodyEmitter* body);

	// Set a receptor's perceptions
	void setPerceptionBody(Body* body);
	void setPerceptionWave(BodyReceptor* receptor);

	// Getter functions
	std::vector<Wave*>* getWaves();
	std::vector<BodyEmitter*>* getEmitters();
	std::vector<BodyReceptor*>* getReceptors();

	void setWaveAmplitude(float amplitudeLoss);

	void clearWaves();

	int getWaveSpeed();
	void setWaveSpeed(int waveSpeed);

	~World(void);
};

#endif



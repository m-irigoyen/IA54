#ifndef ROCKETTERRAINEDITOR_H_
#define ROCKETTERRAINEDITOR_H_

#include <iostream>
#include <SFML/Graphics.hpp>

#include "Problems/Rocket/ProblemRocket.h"
#include "Utilities/MathHelper.h"
#include "Utilities/FilePaths.h"

/*
* The RocketTerrainEditor is a GUI way to load, edit, and save rocket terrains
*/

using namespace std;

class RocketTerrainEditor : public Problem
{
protected:
	// User interface
	sf::Text hud_text;
	std::string currentLevelName;
	sf::CircleShape rocketCircle;

	// Terrain
	ProblemRocket_Terrain terrain;
	deque<pair<int, int>>::iterator selectedPoint;
	bool isPointSelected;


	// PRIVATE FUNCTIONS
	virtual void checkEvents(sf::RenderWindow* window);	// Checks for user input on the problem window
	virtual bool handleEvent(sf::RenderWindow* window, sf::Event event);	// Returns true if event has been dealt with

	virtual void loadTerrain(string path);
	virtual void saveTerrain(string path);
	virtual void generateTerrain(int width = -1, int height = -1);

	void rename();

public:
	RocketTerrainEditor(float waveAmplLossPerSec = 0.0f);

	virtual void run(sf::Time elapsedTime);	// Updating the problem
	virtual void draw(sf::RenderWindow* problemWindow);
	virtual void clean();
	virtual void init();	// init 
	virtual void initGraphics(std::vector<sf::Font>* fonts);
};

#endif


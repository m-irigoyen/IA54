#ifndef PROBLEMROCKET_TERRAIN_H_
#define PROBLEMROCKET_TERRAIN_H_

// The terrain class represents the terrain where the rocket has to land

#define PROBLEMROCKET_TERRAIN_DEFAULTSIZE 1000

#include <deque>
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

#include "pugixml/pugixml.hpp"

#include "Utilities/MathHelper.h"
#include "Utilities/FilePaths.h"

using namespace std;

class ProblemRocket_Terrain
{
protected:
	// Terrain size
	int mapWidth;
	int mapHeight;

	// World specs
	int terrainMaxHeight;
	int terrainMinHeight;
	float windHorizontal;
	float windVertical;
	float gravity;

	// LandingZone
	int terrainFlatZone1;
	int terrainFlatZone2;

	// Rocket start
	float rocketStartX;
	float rocketStartY;
	float rocketStartHSpeed;
	float rocketStartVSpeed;
	float rocketAngle;

	// Terrain points
	deque<pair<int, int>> terrain;	// The terrain. Just specify points, the collision and drawing is automatic

	// Helper functions
	deque<pair<int, int>>::iterator getPointBefore(float x);	// Returns the point contained in this->terrain with closest smallest x compared to given x parameter
	float getTerrainPoint(float x, pair<int, int> p1, pair<int, int> p2);	// Gets the Y coordinate for the given X, with p1.x <=x and p2.x >= x

	// Computes the coordinates of the landing zone. If several are found, only the leftmost one is remembered
	void computeLandingZone();

public:
	// Constructors
	ProblemRocket_Terrain(int width, int height, int maxTerrainHeight, int minTerrainHeight, float rocketStartX, float rocketStartY, float rocketStartHSPeed, float rocketStartVSpeed, float gravity = 4);
	ProblemRocket_Terrain(int width, int height);	// easy constructor
	ProblemRocket_Terrain(string name = "Default");	// Base constructor

	// GUI stuff
	void draw(sf::RenderWindow* window);	// Draws the terrain on given window

	// Loading / saving / generating
	virtual void loadTerrain(std::string name = "Default");
	virtual void saveTerrain(std::string name);
	virtual void generateRandomTerrain(int width = -1, int height = -1);	// Leave -1, -1 to keep the current size

	// Edition functions
	deque<pair<int, int>>::iterator getClosestPointFrom(float x, float y, bool& found, float threshold = 10);
	void reorderPoints();
	void addPoint(float x, float y);
	void addFlat(float x);
	void removePoint(deque<pair<int, int>>::iterator it);

	// GUI Translation functions
	void getWorldCoordinates(float screenX, float screenY, sf::RenderWindow* window, float& worldX, float& worldY);
	void getScreenCoordinates(float worldX, float worldY, float screenWidth, float screenHeight, float& screenX, float& screenY);
	// Terrain interaction
	bool isOnMap(float x, float y);
	bool collides(float x, float y, float hitboxHalfSize);	// Checks if the given position is colliding with terrain
	float getTerrainPoint(float x);	// Gets the Y coordinate for the given X, with p1.x <=x and p2.x >= x

	// Getters
	deque<pair<int, int>>* getTerrain();
	void getLandingZone(float& landing1, float& landing2);
	void getTerrainDimensions(float& terrainWidth, float& terrainHeight);
	int getWidth();
	int getHeight();
	void getRocketStart(float& rocketX, float& rocketY, float& rocketHorizontalSpeed, float& rocketVerticalSpeed, float& rocketAngle);
	void getWind(float& windHorizontal, float& windVertical);
	float getGravity();
	void getHighestPointBeforeLandingZone(float x, float y, float& highestPointX, float& highestPointY);

	//setters
	void setRocketStart(float rocketX, float rocketY);
	void setRocketStartSpeed(float hSpeed, float vSpeed);
	void setWind(float hWind, float vWind);
	void setTerrainWidth(int width);
	void setTerrainHeigh(int height);

	void checkTerrainBounds();

};

#endif
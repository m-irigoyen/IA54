#ifndef PROBLEMROCKET_TERRAIN_H_
#define PROBLEMROCKET_TERRAIN_H_

// The terrain class represents the terrain where the rocket has to land

#include <vector>
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

#include "pugixml/pugixml.hpp"

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

	// Terrain points
	vector<pair<int, int>> terrain;	// The terrain. Just specify points, the collision and drawing is automatic

	// Helper functions
	vector<pair<int, int>>::iterator getPointBefore(float x);	// Returns the point contained in this->terrain with closest smallest x compared to given x parameter
	float getTerrainPoint(float x, pair<int, int> p1, pair<int, int> p2);	// Gets the Y coordinate for the given X, with p1.x <=x and p2.x >= x

public:
	// Constructors
	ProblemRocket_Terrain(int width, int height, int maxTerrainHeight, int minTerrainHeight, float rocketStartX, float rocketStartY, float rocketStartHSPeed, float rocketStartVSpeed, float gravity = 4);
	ProblemRocket_Terrain(int width, int height);	// easy constructor
	ProblemRocket_Terrain(string path = "Default");	// Base constructor

	// GUI stuff
	void draw(sf::RenderWindow* window);	// Draws the terrain on given window

	// Loading / saving / generating
	virtual void loadTerrain(std::string path = "Default");
	virtual void saveTerrain(std::string path);
	virtual void generateRandomTerrain(int width = -1, int height = -1);	// Leave -1, -1 to keep the current size

	// Terrain interaction
	bool isOnMap(float x, float y);
	bool collides(float x, float y);	// Checks if the given position is colliding with terrain
	float getTerrainPoint(float x);	// Gets the Y coordinate for the given X, with p1.x <=x and p2.x >= x

	// Getters
	vector<pair<int, int>>* getTerrain();
	void getLandingZone(float& landing1, float& landing2);
	void getTerrainDimensions(float& terrainWidth, float& terrainHeight);
	int getWidth();
	int getHeight();
	void getRocketStart(float& rocketX, float& rocketY, float& rocketHorizontalSpeed, float& rocketVerticalSpeed);
	void getWind(float& windHorizontal, float& windVertical);
	float getGravity();
};

#endif
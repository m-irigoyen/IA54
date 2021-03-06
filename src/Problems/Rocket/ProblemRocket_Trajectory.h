#ifndef PROBLEMROCKETTRAJECTORY_H_
#define PROBLEMROCKETTRAJECTORY_H_

#include <vector>
#include "SFML/Graphics.hpp"

#include "Utilities/MathHelper.h"

using namespace std;

class ProblemRocket_Trajectory
{
public:
	ProblemRocket_Trajectory();

	void prepareNewTrajectory();
	void inputTrajectory(float x, float y);
	void sucessfulTrajectory();			// Signals current trajectory was successful
	void clearLast();
	void clear();

	void drawAll(sf::RenderWindow* window, int terrainWidth, int terrainHeight);	// Draws all trajectories on screen
	void drawPrevious(sf::RenderWindow* window, int terrainWidth, int terrainHeight);

private:
	vector<pair<vector<pair<float, float>>,bool>> trajectories;	// all the trajectories

	void drawTrajectory(int id, sf::RenderWindow* window, int terrainWidth, int terrainHeight, sf::Color color = sf::Color::Blue);
};


#endif
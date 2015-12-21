#include "ProblemRocket_Trajectory.h"

ProblemRocket_Trajectory::ProblemRocket_Trajectory()
{
	this->prepareNewTrajectory();
}

void ProblemRocket_Trajectory::prepareNewTrajectory()
{
	if (this->trajectories.size() == 0 || this->trajectories.back().size() != 0)
		this->trajectories.push_back(vector<pair<float, float>>());
}

void ProblemRocket_Trajectory::inputTrajectory(float x, float y)
{
	this->trajectories.back().push_back(pair<float, float>(x, y));
}

void ProblemRocket_Trajectory::clearLast()
{
	this->trajectories.pop_back();
}

void ProblemRocket_Trajectory::clear()
{
	this->trajectories.clear();
	this->prepareNewTrajectory();
}

void ProblemRocket_Trajectory::drawAll(sf::RenderWindow * window, int terrainWidth, int terrainHeight)
{
	for (int i = 0; i < this->trajectories.size(); ++i)
	{
		if (i == this->trajectories.size() - 1)
			this->drawTrajectory(i, window, terrainWidth, terrainHeight, sf::Color::Green);
		else
			this->drawTrajectory(i, window, terrainWidth, terrainHeight, sf::Color::Blue);
	}
	
}

void ProblemRocket_Trajectory::drawPrevious(sf::RenderWindow * window, int terrainWidth, int terrainHeight)
{
	if (!this->trajectories.empty())
		this->drawTrajectory(-1, window, terrainWidth, terrainHeight, sf::Color::Green);
}

void ProblemRocket_Trajectory::drawTrajectory(int id, sf::RenderWindow * window, int terrainWidth, int terrainHeight, sf::Color color)
{
	if (this->trajectories.empty())
		return;

	if (id == -1)
		id = this->trajectories.size() - 1;

	for (vector<pair<float, float>>::iterator it = (this->trajectories.end() - 1)->begin(); it != (this->trajectories.end() - 1)->end(); ++it)
	{
		//TODO : draw the point
	}
}

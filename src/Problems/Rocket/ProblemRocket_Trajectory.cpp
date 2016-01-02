#include "ProblemRocket_Trajectory.h"

ProblemRocket_Trajectory::ProblemRocket_Trajectory()
{
	this->prepareNewTrajectory();
}

void ProblemRocket_Trajectory::prepareNewTrajectory()
{
	if (this->trajectories.size() == 0 || this->trajectories.back().first.size() != 0)
	{
		this->trajectories.push_back(pair<vector<pair<float, float>>, bool>());
		this->trajectories.back().second = false;
	}
}

void ProblemRocket_Trajectory::inputTrajectory(float x, float y)
{
	// Checking if 
	if (!this->trajectories.empty() && !this->trajectories.back().first.empty() && this->trajectories.back().first.back().first == x && this->trajectories.back().first.back().first == y)
	{
		// Don't remember the same position twice
		return;
	}
	else
	{
		// If trajectories aren't ready, prepare it
		if (this->trajectories.empty())
			this->prepareNewTrajectory();

		this->trajectories.back().first.push_back(pair<float, float>(x, y));
	}
}

void ProblemRocket_Trajectory::sucessfulTrajectory()
{
	if (this->trajectories.empty() || this->trajectories.back().first.empty())
		return;
	else
		this->trajectories.back().second = true;
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
			this->drawTrajectory(i, window, terrainWidth, terrainHeight, sf::Color::Blue);
		else
			this->drawTrajectory(i, window, terrainWidth, terrainHeight, sf::Color::Green);
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

	// don't draw unless there are 2 points
	if (this->trajectories.at(id).first.size() < 2)
		return;

	// Checking if it's a succesful trajectory
	if (color == sf::Color::Green && !this->trajectories.at(id).second)
		color = sf::Color::Red;

	vector<pair<float, float>>::iterator p = (this->trajectories.at(id).first).begin() + 1;
	for (vector<pair<float, float>>::iterator it = (this->trajectories.at(id).first).begin(); it != (this->trajectories.at(id).first).end(); ++it)
	{
		// We resize the terrain in perspective, so that the terrain takes up all the width and height of the screen
		sf::Vertex line[] =
		{
			sf::Vertex(sf::Vector2f(p->first*window->getSize().x / terrainWidth,
			(terrainHeight - p->second)*window->getSize().y / terrainHeight), color),
			sf::Vertex(sf::Vector2f(it->first*window->getSize().x / terrainWidth,
				(terrainHeight - it->second)*window->getSize().y / terrainHeight), color)
		};

		window->draw(line, 2, sf::Lines);

		p = it;
	}
}

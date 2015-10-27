#include "ProblemDrones.h"

ProblemDrones::ProblemDrones(std::map<int, DRONE_BEHAVIOURS> behaviourTable, int numberOfDrones)
{
}

void ProblemDrones::run(sf::Time elapsedTime)
{
	this->unityConnection.receiveData(&this->messages);

	while (!messages.empty())
	{
		std::cout << "ProblemDrones::run : Received message : " << messages.front() << std::endl;
		messages.pop_front();
	}
}

void ProblemDrones::replicatePositions()
{
	for (std::map<int, pos3>::iterator it = this->dronePositions.begin(); it != this->dronePositions.end(); ++it)
	{
		string message;
		message.insert(message.size(), std::to_string(it->first));
		cout << "ProblemDrones::replicatePositions : sending : " << message << endl << "size : " << endl;
		this->unityConnection.sendData(message);
	}
}

bool ProblemDrones::init(int portNumber)
{
	return this->unityConnection.initConnection(portNumber);
}

int ProblemDrones::getNbDrones()
{
	return this->nbDrones;
}

void ProblemDrones::setNbDrones(int nbDrones)
{
	if (nbDrones > 1)
		this->nbDrones = nbDrones;
}

pos3 ProblemDrones::getPos(int droneId)
{
	

	map<int, pos3>::iterator it = this->dronePositions.find(droneId);

	if (it != this->dronePositions.end())
	{
		return it->second;
	}
	std::cout << "ProblemDrones::getPos : ERROR : couldn't find droneId" << std::endl;
	return pos3();
}

void ProblemDrones::setPos(int droneId, pos3 pos)
{
	if (this->dronePositions.count(droneId) == 0)
		this->dronePositions.insert(pair<int, pos3>(droneId, pos));
	else
	{
		// Searching if that droneId already exists in the map
		std::map<int, pos3>::iterator it = this->dronePositions.find(droneId);
		if (it != this->dronePositions.end())
			it->second = pos; // Found one
		else
			this->dronePositions.insert(std::pair<int, pos3>(droneId, pos)); // Couldn't find one, insert it
	}
}

void ProblemDrones::setDroneOrder(int droneId, droneOrder order)
{
	if (this->droneCommands.count(droneId) == 0)
		this->droneCommands.insert(pair<int, droneOrder>(droneId, order));
	else
	{
		// Searching if that droneId already exists in the map
		std::map<int, droneOrder>::iterator it = this->droneCommands.find(droneId);
		if (it != this->droneCommands.end())
			it->second = order; // Found one
		else
			this->droneCommands.insert(std::pair<int, droneOrder>(droneId, order)); // Couldn't find one, insert it
	}
}

// Gets corresponding behaviour to given frequency
DRONE_BEHAVIOURS ProblemDrones::getBehaviour(int frequency)
{
	// Go through the look up table of behaviours
	for (map<int, DRONE_BEHAVIOURS>::iterator it = this->behaviourTable.begin(); it != this->behaviourTable.end(); ++it)
	{
		// We went too far : frequency is now smaller than the one we're looking at
		if (frequency >= it->first-FREQUENCY_MARGIN_D && frequency <= it->first + FREQUENCY_RANGE_D + FREQUENCY_MARGIN_D)
		{
			return it->second;
		}
	}
	
	return DRONE_BEHAVIOURS::hover;
}

DRONE_BEHAVIOURS ProblemDrones::getBehaviour(float frequency)
{
	return this->getBehaviour((int) frequency);
}

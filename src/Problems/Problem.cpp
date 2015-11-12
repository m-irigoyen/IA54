#include "Problem.h"

Problem::Problem(float waveAmplLossPerSec, bool useAttenuation) : waveAmplLossPerSec(waveAmplLossPerSec), problemLive(true), useWaveAttenuation(useAttenuation)
{
}

void Problem::checkEvents(sf::RenderWindow * window)
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		handleEvent(window, event);
	}
}

bool Problem::handleEvent(sf::RenderWindow* window, sf::Event event)
{
	switch (event.type)
	{
	case sf::Event::Closed:
		window->close();
		return true;
	case sf::Event::KeyPressed:
		switch (event.key.code)
		{
		case::sf::Keyboard::Escape:
			window->close();
			return true;
		}
	}
	return false;
}

float Problem::getAmplitudeLoss()
{
	return this->waveAmplLossPerSec;
}

bool Problem::getProblemLive()
{
	return this->problemLive;
}

bool Problem::isUsingAttenuation()
{
	return this->useWaveAttenuation;
}

int Problem::getNumberOfEmitters()
{
	return this->numberOfEmitters;
}

int Problem::getNumberOfReceptors()
{
	return this->numberOfReceptors;
}

void Problem::setNumberOfEmitters(int nb)
{
	if (nb < 0)
		nb = 0;
	this->numberOfEmitters = nb;
}

void Problem::setNumberOfReceptors(int nb)
{
	if (nb < 0)
		nb = 0;
	this->numberOfEmitters = nb;
}

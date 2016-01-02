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
		case::sf::Keyboard::P : 
			this->pause = toggle(this->pause);
			return true;
		}
		break;
	case sf::Event::Resized:
		window->setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
		return true;
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

bool Problem::getResetAgent()
{
	if (this->resetAgents)
	{
		//FIXME : why isn't that working ? u_u
		resetAgents = false;
		return true;
	}
		
	return false;
}


float Problem::getWaveAmplitudeOffset()
{
	return this->wave_amplitude_offset;
}

float Problem::getWaveAmplitudeRange()
{
	return this->wave_amplitude_range;
}

float Problem::getWaveFrequencyOffset()
{
	return this->wave_frequency_offset;
}

float Problem::getWaveFrequencyRange()
{
	return this->wave_frequency_range;
}

bool Problem::getPause()
{
	return this->pause;
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

void Problem::setPause(bool pause)
{
	this->pause = pause;
}

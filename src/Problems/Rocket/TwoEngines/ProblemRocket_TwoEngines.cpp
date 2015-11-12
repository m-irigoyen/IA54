#include "Problems/Rocket/TwoEngines/ProblemRocket_TwoEngines.h"


ProblemRocket_TwoEngines::ProblemRocket_TwoEngines(float waveAmplLossPerSec) : ProblemRocket(waveAmplLossPerSec)
{
	
}

void ProblemRocket_TwoEngines::getThrustForce(double & hForce, double & vForce)
{
	double vecX = cos(degToRad(this->rocket_angle));
	double vecY = sin(degToRad(this->rocket_angle));

	hForce = ((this->rocket_enginesPower.at(0) * this->rocket_engineThrust.at(0) * vecX) + (this->rocket_enginesPower.at(1) * this->rocket_engineThrust.at(1) * vecX)) / 100;
	vForce = ((this->rocket_enginesPower.at(0) * this->rocket_engineThrust.at(0) * vecY) + (this->rocket_enginesPower.at(1) * this->rocket_engineThrust.at(1) * vecY)) / 100;
	
	//TODO: IF : calculer la rotation que donne la puissance des moteurs actuelles

	// this->rocket_enginePower.at(0) : moteur gauche
	// this->rocket_enginePower.at(1) : moteur droit
	
	// La variation de l'angle a calculer. Les angles sont en sens trigonométriques : donc un angle positif équivaut à une rotation anti horaire. Donc si le moteur droit est plus fort que le gauche, l'angle devrait être positif.
	// this->rotationChange = ?
}

void ProblemRocket_TwoEngines::checkEvents(sf::RenderWindow * window)
{
	// Checking events
	if (window != NULL)
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			handleEvent(window, event);
		}
	}

	// KeyDown events
	if (this->userControlled)
	{
		// Engine control
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			this->setDesiredPower(0, 1);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
			this->setDesiredPower(0, -1);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
			this->setDesiredPower(1, 1);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			this->setDesiredPower(1, -1);
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			this->setDesiredPower(0, -1);
			this->setDesiredPower(1, -1);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			this->setDesiredPower(0, 1);
			this->setDesiredPower(1, 1);
		}

		// Angle control
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			this->setDesiredAngle(-1);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			this->setDesiredAngle(+1);
	}
	
}

bool ProblemRocket_TwoEngines::handleEvent(sf::RenderWindow * window, sf::Event event)
{
	if (ProblemRocket::handleEvent(window, event))
		return true;
	else
		return false;
}

void ProblemRocket_TwoEngines::resolveRocketPowerChange()
{
	for (int i = 0; i < this->powerChange.size(); ++i)
	{
		if (this->userControlled || this->useGradualChange)
		{
			this->rocket_enginesPower.at(i) += this->constrainPowerChange(this->rocket_enginesPower.at(i), this->powerChange.at(i));
			this->rocket_enginesPower.at(i) = this->constrainPower(this->rocket_enginesPower.at(i));

			// Resetting the change
			this->desiredPower.at(i) = 0;
			this->powerChange.at(i) = 0;
		}
		else
		{
			this->rocket_enginesPower.at(i) += this->constrainPowerChange(this->rocket_enginesPower.at(i), this->powerChange.at(i) - this->rocket_enginesPower.at(i));
			this->rocket_enginesPower.at(i) = this->constrainPower(this->rocket_enginesPower.at(i));
		}
	}
}

void ProblemRocket_TwoEngines::resolveRocketAngleChange()
{
	this->rocket_angle += this->rotationChange;
	this->rotationChange = 0;
	this->desiredRotation = 0;

	this->rocket_angle = this->constrainAngle(this->rocket_angle);
}

void ProblemRocket_TwoEngines::resolveInfluences()
{
	this->powerChange = this->desiredPower;
	// No need to do the angle : it's already computed in the getThrustForce function
}

void ProblemRocket_TwoEngines::run(sf::Time elapsedTime)
{
	if (!hasLanded && !hasCrashed && !hasGoneMissing && this->problemLive)
	{
		// First off : get the thrust force
		double hOffset, vOffset;
		this->getThrustForce(hOffset, vOffset);

		// Move the rocket by this force
		this->moveRocket(elapsedTime, hOffset, vOffset);

		// Now, resolve influences
		this->resolveInfluences();

		this->resolveRocketPowerChange();
		this->resolveRocketAngleChange();

		this->resetDesiredChanges();
	}
	else
		this->problemLive = false;
}

// Draw the problem
void ProblemRocket_TwoEngines::draw(sf::RenderWindow * problemWindow)
{
	this->checkEvents(problemWindow);

	ProblemRocket::draw(problemWindow);

	// Drawing engine fire left
	if (this->rocket_enginesPower.at(0) > 0)
	{
		this->hud_engineFire.setSize(sf::Vector2f(this->rocket_enginesPower.at(0) * HUD_SIZE_THRUSTER/2, 6));
		this->hud_engineFire.setOrigin(this->rocket_enginesPower.at(0) * HUD_SIZE_THRUSTER/2 + this->hud_rocketSprite.getLocalBounds().width / 2, 3 + 10);
		this->hud_engineFire.setRotation(-this->rocket_angle);
		this->hud_engineFire.setPosition(this->rocket_x * problemWindow->getSize().x / this->terrain.getWidth(),
			problemWindow->getSize().y - (this->rocket_y * problemWindow->getSize().y / this->terrain.getHeight()));

		problemWindow->draw(this->hud_engineFire);
	}
	// Drawing engine fire right
	if (this->rocket_enginesPower.at(1) > 0)
	{
		this->hud_engineFire.setSize(sf::Vector2f(this->rocket_enginesPower.at(1) * HUD_SIZE_THRUSTER/2, 6));
		this->hud_engineFire.setOrigin(this->rocket_enginesPower.at(1) * HUD_SIZE_THRUSTER/2 + this->hud_rocketSprite.getLocalBounds().width / 2, 3 - 10);
		this->hud_engineFire.setRotation(-this->rocket_angle);
		this->hud_engineFire.setPosition(this->rocket_x*problemWindow->getSize().x / this->terrain.getWidth(),
			problemWindow->getSize().y - (this->rocket_y*problemWindow->getSize().y / this->terrain.getHeight()));

		problemWindow->draw(this->hud_engineFire);
	}

	// Drawing text
	string temp;
	temp = std::to_string(this->rocket_enginesPower.at(0));
	this->hud_text.setString("PowerLeft  : " + temp);
	this->hud_text.setPosition(10, 65);
	problemWindow->draw(this->hud_text);

	temp = std::to_string(this->rocket_enginesPower.at(1));
	this->hud_text.setString("PowerRight : " + temp);
	this->hud_text.setPosition(10, 85);
	problemWindow->draw(this->hud_text);
}

void ProblemRocket_TwoEngines::clean()
{
}

void ProblemRocket_TwoEngines::init()
{
	// Init engines
	this->rocket_enginesPower.push_back(0);
	this->rocket_engineThrust.push_back(PROBLEMROCKET_ROCKET_THRUST_BASE/2);

	this->rocket_enginesPower.push_back(0);
	this->rocket_engineThrust.push_back(PROBLEMROCKET_ROCKET_THRUST_BASE/2);

	this->desiredPower.push_back(0);
	this->powerChange.push_back(0);
	this->desiredPower.push_back(0);
	this->powerChange.push_back(0);

	this->loadTerrain("Default");
}

void ProblemRocket_TwoEngines::initGraphics(std::vector<sf::Font>* fonts)
{
	ProblemRocket::initGraphics(fonts);

	// Engine fire
	this->hud_engineFire.setFillColor(sf::Color::Yellow);
	this->hud_engineFire.setOutlineColor(sf::Color::Red);
	this->hud_engineFire.setOutlineThickness(1);
	this->hud_engineFire.setSize(sf::Vector2f(50/2,6));
	this->hud_engineFire.setOrigin(0, 3);
}

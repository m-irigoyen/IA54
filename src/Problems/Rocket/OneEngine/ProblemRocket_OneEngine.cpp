#include "Problems/Rocket/OneEngine/ProblemRocket_OneEngine.h"


ProblemRocket_OneEngine::ProblemRocket_OneEngine(float waveAmplLossPerSec) : ProblemRocket(waveAmplLossPerSec)
{
	this->userControlled = true;
}

void ProblemRocket_OneEngine::getThrustForce(double & hForce, double & vForce)
{
	double vecX = cos(degToRad(this->rocket_angle));
	double vecY = sin(degToRad(this->rocket_angle));

	hForce = (this->rocket_enginesPower.at(0) * this->rocket_engineThrust.at(0) * vecX) / 100;
	vForce = (this->rocket_enginesPower.at(0) * this->rocket_engineThrust.at(0) * vecY) / 100;
}

void ProblemRocket_OneEngine::checkEvents(sf::RenderWindow * window)
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		this->handleEvent(window, event);
	}

	// Engine control
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (this->userControlled)
			this->setDesiredPower(0,1);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (this->userControlled)
			this->setDesiredPower(0,-1);
	}

	// Angle control
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (this->userControlled)
			this->setDesiredAngle(-1);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if (this->userControlled)
			this->setDesiredAngle(1);
	}
}

bool ProblemRocket_OneEngine::handleEvent(sf::RenderWindow * window, sf::Event event)
{
	if (ProblemRocket::handleEvent(window, event))
		return true;
	else
		return false;
}

void ProblemRocket_OneEngine::resolveRocketPowerChange()
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

void ProblemRocket_OneEngine::resolveRocketAngleChange()
{
	// Gradual change : rotate by the desiredRotation
	if (this->userControlled || this->useGradualChange)
	{
		this->rocket_angle += this->rotationChange;
		this->rotationChange = 0;
		this->desiredRotation = 0;
	}
		
	// Hard change : set angle to desiredRotation
	else
	{
		this->rotationChange += PROBLEMROCKET_GUI_ANGLE_OFFSET;
		this->rocket_angle = this->rotationChange;
	}
		
	this->rocket_angle = this->constrainAngle(this->rocket_angle);
}

void ProblemRocket_OneEngine::resolveInfluences()
{
	this->rotationChange = this->desiredRotation;
	this->powerChange = this->desiredPower;
}

void ProblemRocket_OneEngine::run(sf::Time elapsedTime)
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
void ProblemRocket_OneEngine::draw(sf::RenderWindow * problemWindow)
{
	this->checkEvents(problemWindow);

	ProblemRocket::draw(problemWindow);

	// Drawing engine fire
	if (this->rocket_enginesPower.at(0) > 0)
	{
		this->hud_engineFire.setSize(sf::Vector2f(this->rocket_enginesPower.at(0) * PROBLEMROCKET_GUI_SIZE_THRUSTER, 6));
		this->hud_engineFire.setOrigin(this->rocket_enginesPower.at(0) * PROBLEMROCKET_GUI_SIZE_THRUSTER + this->hud_rocketSprite.getLocalBounds().width/2, 3);
		this->hud_engineFire.setRotation(-this->rocket_angle);
		this->hud_engineFire.setPosition(this->rocket_x*problemWindow->getSize().x / this->terrain.getWidth(),
			problemWindow->getSize().y - (this->rocket_y * problemWindow->getSize().y / this->terrain.getHeight()));

		problemWindow->draw(this->hud_engineFire);
	}

	// Drawing text
	string temp;
	temp = std::to_string(this->rocket_enginesPower.at(0));
	this->hud_text.setString("Power  : " + temp);
	this->hud_text.setPosition(10, 65);
	problemWindow->draw(this->hud_text);
}

void ProblemRocket_OneEngine::clean()
{
}

void ProblemRocket_OneEngine::init()
{
	this->rocket_enginesPower.push_back(0);
	this->rocket_engineThrust.push_back(PROBLEMROCKET_ROCKET_THRUST_BASE);

	this->desiredPower.push_back(0);
	this->powerChange.push_back(0);

	this->loadTerrain("Default");
}

void ProblemRocket_OneEngine::initGraphics(std::vector<sf::Font>* fonts)
{
	ProblemRocket::initGraphics(fonts);

	// Engine fire
	this->hud_engineFire.setFillColor(sf::Color::Yellow);
	this->hud_engineFire.setOutlineColor(sf::Color::Red);
	this->hud_engineFire.setOutlineThickness(1);
	this->hud_engineFire.setSize(sf::Vector2f(50,6));
	this->hud_engineFire.setOrigin(0, 3);
}
#include "Problems/Rocket/OneEngine/ProblemRocket_OneEngine.h"


ProblemRocket_OneEngine::ProblemRocket_OneEngine(float waveAmplLossPerSec) : ProblemRocket(waveAmplLossPerSec)
{
	
}

void ProblemRocket_OneEngine::getThrustForce(float & hForce, float & vForce)
{
	float vecX = cos(degToRad(this->rocket_angle));
	float vecY = sin(degToRad(this->rocket_angle));

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

void ProblemRocket_OneEngine::initUserControl(bool userControl)
{
	if (userControl)
		this->userControlled = true;
	else
		this->userControlled = false;
}

void ProblemRocket_OneEngine::resolveRocketPowerChange()
{
	for (int i = 0; i < this->rocket_enginesPower.size(); ++i)
	{
		this->rocket_enginesPower.at(i) = this->constrainPowerChange(this->rocket_enginesPower.at(i), this->powerChange.at(i));
	}
}

void ProblemRocket_OneEngine::resolveRocketAngleChange()
{		
	// If the rotationChange is not a relative value, add the GUI offset
	if (!this->useRelativeChange)
	{
		this->rotationChange += PROBLEMROCKET_GUI_ANGLE_OFFSET;
	}
		
	this->rocket_angle = this->constrainAngleChange(this->rocket_angle, this->rotationChange);
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
		float hOffset, vOffset;
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
	// Engines
	this->rocket_enginesPower.push_back(0);
	this->rocket_engineThrust.push_back(PROBLEMROCKET_ROCKET_THRUST_BASE);
	this->desiredPower.push_back(0);
	this->powerChange.push_back(0);

	// Rocket specs
	this->rocket_engineChangeRate = 1;
	this->rocket_rotationRate = 0.5;

	// Control mode
	this->userControlled = false;
	this->useRelativeChange = true;

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
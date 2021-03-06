#include "Problems/Rocket/OneEngine/ProblemRocket_OneEngine.h"


ProblemRocket_OneEngine::ProblemRocket_OneEngine(float waveAmplLossPerSec) : ProblemRocket(waveAmplLossPerSec)
{
	this->setMaxAngle(PROBLEMROCKET_LANDING_MAXANGLE);
	this->setMaxHSpeed(PROBLEMROCKET_LANDING_MAXHSPEED);
	this->setMaxVSpeed(PROBLEMROCKET_LANDING_MAXVSPEED);
	this->problemPowerOffset = 2.0f;
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
	{
		this->userControlled = true;
		this->useRelativeChange = true;
	}
	else
	{
		this->userControlled = false;
	}
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

void ProblemRocket_OneEngine::initRocketStartPower(float startPower)
{
	this->rocket_enginesPower.at(0) = startPower;
}

void ProblemRocket_OneEngine::resolveInfluences()
{
	this->rotationChange = this->desiredRotation;
	this->powerChange = this->desiredPower;
}


// Draw the problem
void ProblemRocket_OneEngine::draw(sf::RenderWindow * problemWindow)
{
	this->checkEvents(problemWindow);

	if (this->problemLive)
	{
		// Drawing engine fire
		if (this->rocket_enginesPower.at(0) > 0)
		{
			this->hud_engineFire.setSize(sf::Vector2f(this->rocket_enginesPower.at(0) * (PROBLEMROCKET_GUI_SIZE_THRUSTER), 6));
			//this->hud_engineFire.setScale(this->hud_rocketSprite.getScale().x, this->hud_rocketSprite.getScale().y);
			this->hud_engineFire.setScale(this->hud_rocketSprite.getScale().x, 1);

			this->hud_engineFire.setOrigin(this->rocket_enginesPower.at(0) * PROBLEMROCKET_GUI_SIZE_THRUSTER + (this->hud_rocketSprite.getLocalBounds().width)*(this->hud_rocketSprite.getScale().x) / 2 +15,
				3);
			this->hud_engineFire.setRotation(-this->rocket_angle);
			this->hud_engineFire.setPosition(this->rocket_x*problemWindow->getSize().x / this->terrain.getWidth(),
				problemWindow->getSize().y - (this->rocket_y * problemWindow->getSize().y / this->terrain.getHeight()));

			problemWindow->draw(this->hud_engineFire);
		}
	}


	if (this->drawHUD)
	{
		// Drawing text
		string temp;

		// Title
		this->hud_text.setCharacterSize(30);
		this->hud_text.setString("Rocket : One Engine");
		this->hud_text.setPosition(problemWindow->getSize().x / 2 - this->hud_text.getGlobalBounds().width / 2, 5);
		problemWindow->draw(this->hud_text);

		// Engines
		this->hud_text.setCharacterSize(20);
		temp = std::to_string(this->rocket_enginesPower.at(0));
		this->hud_text.setString("Power  : " + temp);
		this->hud_text.setPosition(10, 85);
		problemWindow->draw(this->hud_text);
	}
	
	ProblemRocket::draw(problemWindow);
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
	this->rocket_engineChangeRate = 0.1f;
	this->rocket_rotationRate = 0.1f;

	// Control mode
	this->userControlled = false;
	this->useRelativeChange = false;

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

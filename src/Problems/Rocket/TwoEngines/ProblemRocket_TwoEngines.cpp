#include "Problems/Rocket/TwoEngines/ProblemRocket_TwoEngines.h"


ProblemRocket_TwoEngines::ProblemRocket_TwoEngines(float waveAmplLossPerSec) : ProblemRocket(waveAmplLossPerSec)
{
	
}

void ProblemRocket_TwoEngines::getThrustForce(float & hForce, float & vForce)
{
	float vecX = cos(degToRad(this->rocket_angle));
	float vecY = sin(degToRad(this->rocket_angle));

	hForce = ((this->rocket_enginesPower.at(0) * this->rocket_engineThrust.at(0) * vecX) + (this->rocket_enginesPower.at(1) * this->rocket_engineThrust.at(1) * vecX)) / 100;
	vForce = ((this->rocket_enginesPower.at(0) * this->rocket_engineThrust.at(0) * vecY) + (this->rocket_enginesPower.at(1) * this->rocket_engineThrust.at(1) * vecY)) / 100;
	

	float angleLeft = convertToRange(this->rocket_enginesPower.at(0),
		0,
		this->getPowerMax(),
		0,
		PROBLEMROCKET_TWO_MAXENGINEROTATION);

	float angleRight = convertToRange(this->rocket_enginesPower.at(1),
		0,
		this->getPowerMax(),
		0,
		PROBLEMROCKET_TWO_MAXENGINEROTATION);

	this->rotationChange = angleRight - angleLeft;

	//TODO: IF : calculer la rotation que donne la puissance des moteurs actuelles

	// this->rocket_enginePower.at(0) : moteur gauche
	// this->rocket_enginePower.at(1) : moteur droit
	
	// La variation de l'angle a calculer. Les angles sont en sens trigonom�triques : donc un angle positif �quivaut � une rotation anti horaire. Donc si le moteur droit est plus fort que le gauche, l'angle devrait �tre positif.
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

void ProblemRocket_TwoEngines::initUserControl(bool userControl)
{
	if (userControl)
		this->userControlled = true;
	else
		this->userControlled = false;
}

void ProblemRocket_TwoEngines::resolveRocketPowerChange()
{
	for (int i = 0; i < this->rocket_enginesPower.size(); ++i)
	{
		this->rocket_enginesPower.at(i) = this->constrainPowerChange(this->rocket_enginesPower.at(i), this->powerChange.at(i));
	}
}

void ProblemRocket_TwoEngines::resolveRocketAngleChange()
{
	this->rocket_angle = this->constrainAngleChange(this->rocket_angle, this->rotationChange);
}

void ProblemRocket_TwoEngines::resolveInfluences()
{
	this->powerChange = this->desiredPower;
	// No need to do the angle : it's already computed in the getThrustForce function
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

	// Title
	this->hud_text.setCharacterSize(30);
	this->hud_text.setString("Rocket : Two Engines");
	this->hud_text.setPosition(problemWindow->getSize().x / 2 - this->hud_text.getLocalBounds().width / 2, 5);
	problemWindow->draw(this->hud_text);

	this->hud_text.setCharacterSize(20);
	temp = std::to_string(this->rocket_enginesPower.at(0));
	this->hud_text.setString("PowerLeft  : " + temp);
	this->hud_text.setPosition(10, 85);
	problemWindow->draw(this->hud_text);

	temp = std::to_string(this->rocket_enginesPower.at(1));
	this->hud_text.setString("PowerRight : " + temp);
	this->hud_text.setPosition(10, 105);
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

	// Rocket specs
	this->rocket_engineChangeRate = 1;
	this->rocket_rotationRate = 0.5;

	// Control mode
	this->userControlled = true;
	this->useRelativeChange = true;

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

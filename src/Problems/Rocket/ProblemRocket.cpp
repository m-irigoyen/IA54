#include "ProblemRocket.h"

bool ProblemRocket::correctLanding(double hSpeed, double vSpeed, double angle)
{
	return false;
}

// Given the hSpeed and vSpeed values, move the Rocket
void ProblemRocket::moveRocket(sf::Time elapsedTime, double hEnginesForce, double vEnginesForce)
{
	// Moving the rocket
	this->rocket_x += this->rocket_hSpeed * elapsedTime.asSeconds();
	this->rocket_y += this->rocket_vSpeed * elapsedTime.asSeconds() - (this->terrain.getGravity()*elapsedTime.asSeconds());

	//cout << hSpeed << " / " << vSpeed << endl;

	// If collides with terrain
	if (this->terrain.collides(this->rocket_x, this->rocket_y))
	{
		// If is on flat zone
		double flat1, flat2;
		this->terrain.getLandingZone(flat1, flat2);
		if (this->rocket_x >= flat1 && rocket_y <= flat2)
		{
			if (this->correctLanding(this->rocket_hSpeed, this->rocket_vSpeed, this->rocket_angle))
			{
				this->hasLanded = true;
				cout << "Rocket has landed safely!" << endl;
			}
			else
			{
				this->hasCrashed = true;
				cout << "Rocket has crashed ! The landing wasn't safe enough!" << endl;
			}
		}
		else
		{
			this->hasCrashed = true;
			cout << "Rocket crashed : landed on non flat zone!" << endl;
		}
	}
}

void ProblemRocket::getThrustersForce(double& hForce, double& vForce)
{
	//TODO : override that in child classes
	hForce = 0;
	vForce = 0;
}

// Checks for user input
void ProblemRocket::checkEvents(sf::RenderWindow* window)
{
	// Calling parent class event check
	Problem::checkEvents(window);

	if (window != NULL)
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyPressed:
				switch (event.key.code)
				{
				case::sf::Keyboard::F1:
					this->userControlled = true;
					break;
				case::sf::Keyboard::F2:
					this->userControlled = false;
					break;
				}
			}
		}
	}
}

// returns the given angle constrained so 0 <= angle < 360
double ProblemRocket::constrainAngle(double angle)
{
	// constrain angle
	while (angle >= 360)
		angle -= 360;
	while (angle < 0)
		angle += 360;
	return angle;
}

ProblemRocket::ProblemRocket(float waveAmplLossPerSec, bool useAttenuation) : Problem(waveAmplLossPerSec, useAttenuation), userControlled(false), rocketRotationRate(-1), engineChangeRate(-1)
{
}

void ProblemRocket::run(sf::Time elapsedTime)
{
	double hOffset, vOffset;
	this->getThrustersForce(hOffset, vOffset);
	this->rotateRocket();

	this->moveRocket(elapsedTime, hOffset, vOffset);
}

void ProblemRocket::clean()
{
	
}

// Resets rocket to start position
void ProblemRocket::resetRocket()
{
	this->terrain.getRocketStart(this->rocket_x, this->rocket_y, this->rocket_hSpeed, this->rocket_vSpeed);
}

void ProblemRocket::init()
{
	this->resetRocket();
}

void ProblemRocket::initGraphics(std::vector<sf::Font>* fonts)
{
	// Text
	this->hud_text.setFont(fonts->at(0));
	this->hud_text.setCharacterSize(20);
	this->hud_text.setColor(sf::Color::White);

	// Rocket sprite
	string path;
	path += PATH_RES_FONTS;
	path += "Rocket.png";
	if (!this->hud_rocketTexture.loadFromFile(path))
	{
		std::cout << "ProblemRocket::init : ERROR : couldn't load rocket image from disk." << std::endl;
	}
	this->hud_rocketSprite.setTexture(hud_rocketTexture);
	this->hud_rocketSprite.setOrigin(hud_rocketTexture.getSize().x / 2, hud_rocketTexture.getSize().y / 2);

	// Engine fire
	this->hud_engineFire.setFillColor(sf::Color::Yellow);
	this->hud_engineFire.setOutlineColor(sf::Color::Red);
	this->hud_engineFire.setOutlineThickness(1);
	this->hud_engineFire.setSize(sf::Vector2f(50, 6));
}

void ProblemRocket::draw(sf::RenderWindow * window, std::vector<sf::Font>* fonts)
{
	this->checkEvents(window);

	// Drawing terrain
	//TODO: draw the terrain
	// Drawing terrain
	this->terrain.draw(window);

	// Engine fire must be drawn in child classes
	//TODO: transfer that in child classes
	/*if (this->enginePower > 0)
	{
		this->hud_engineFire.setSize(sf::Vector2f(this->enginePower*HUD_SIZE_THRUSTER, 6));
		this->hud_engineFire.setOrigin(this->enginePower*HUD_SIZE_THRUSTER + this->hud_rocketSprite.getLocalBounds().width / 2, 3);
		this->hud_engineFire.setRotation(-this->rocketAngle);
		this->hud_engineFire.setPosition(rocketX*problemWindow->getSize().x / worldWidth,
			problemWindow->getSize().y - (rocketY*problemWindow->getSize().y / worldHeight));

		problemWindow->draw(this->hud_engineFire);
	}*/

	// Drawing rocket
	this->hud_rocketSprite.setPosition(this->rocket_x * window->getSize().x / this->terrain.getWidth(),
		window->getSize().y - (this->rocket_y * window->getSize().y / this->terrain.getHeight()));
	this->hud_rocketSprite.setRotation(-this->rocket_angle);

	window->draw(this->hud_rocketSprite);

	// Drawing HUD
	string temp;
	temp = std::to_string(this->rocket_angle - PROBLEMROCKET_GUI_ANGLE_OFFSET);
	this->hud_text.setPosition(10, 5);
	this->hud_text.setString("Angle  : " + temp);
	window->draw(this->hud_text);

	temp = std::to_string(this->rocket_hSpeed);
	this->hud_text.setPosition(10, 25);
	this->hud_text.setString("hSpeed : " + temp);
	window->draw(this->hud_text);

	temp = std::to_string(this->rocket_vSpeed);
	this->hud_text.setPosition(10, 45);
	this->hud_text.setString("vSpeed : " + temp);
	window->draw(this->hud_text);

	// Engine values must be drawned in other classes
}

void ProblemRocket::loadTerrain(string path)
{
	this->terrain.loadTerrain(path);
	this->resetRocket();
}

void ProblemRocket::generateTerrain(int width, int height)
{
	this->terrain.generateRandomTerrain(width, height);
	this->resetRocket();
}

bool ProblemRocket::getHasLanded()
{
	return this->hasLanded;
}

bool ProblemRocket::getHasCrashed()
{
	return this->hasCrashed;
}

bool ProblemRocket::getHasGoneMissing()
{
	return this->hasGoneMissing;
}

// Sets the desired power : the rocket will power up (or down) its engines until they reach the given value
void ProblemRocket::setDesiredPower(int engineNumber, int power)
{
	if (engineNumber >= 0 && engineNumber < this->desiredPower.size())
		this->desiredPower.at(engineNumber) = power;
}

// Sets the desired angle : the rocket will rotate until it reaches the given angle
void ProblemRocket::setDesiredAngle(double angle)
{
	angle += PROBLEMROCKET_GUI_ANGLE_OFFSET;	// Applying offset to have 0° be up
	angle = constrainAngle(angle);
	this->desiredRotation = angle;
}

// Sets the desired power change : the rocket will power up (or down) by the given amount (limited by the rocket's capabilities)
void ProblemRocket::setDesiredPowerChange(int engineNumber, int power)
{
	if (engineNumber >= 0 && engineNumber < this->desiredPower.size())
		this->desiredPower.at(engineNumber) = power;
}

// Sets the desired angle change : the rocket will rotate by the given amount (limited by the rocket's capabilities)
void ProblemRocket::setDesiredAngleChange(double angle)
{
	this->desiredRotationChange = angle;
}



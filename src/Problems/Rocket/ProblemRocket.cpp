#include "ProblemRocket.h"

/*
Checks if the rocket landed correctly.
We assume that a correct landing means :
|hSpeed| < 20
|vSpeed| < 40
-5 <= rocketAngle <= 5
*/
bool ProblemRocket::correctLanding(float hSpeed, float vSpeed, float angle)
{
	if (angle >= PROBLEMROCKET_GUI_ANGLE_OFFSET - 10 && angle <= PROBLEMROCKET_GUI_ANGLE_OFFSET + 10)	// Don't forget to check for the angle offset
	{
		if (hSpeed >= -20.0f && hSpeed <= 20.0f)
		{
			if (vSpeed <= 0.0f && vSpeed >= -40.0f)	// Can't collide going up
			{
				cout << "Rocket landed successfully!" << endl;
				return true;
			}
			else
				cout << "Rocket crashed : verticalSpeed was too big!" << endl;
		}
		else
			cout << "Rocket crashed : horizontalSpeed was too big!" << endl;
	}
	else
		cout << "Rocket crashed : angle was bigger than 5 (or smaller than -5)!" << endl;
	return false;
}

// Given the hSpeed and vSpeed values, move the Rocket
void ProblemRocket::moveRocket(sf::Time elapsedTime, float hEnginesForce, float vEnginesForce)
{
	float hWind, vWind;
	this->terrain.getWind(hWind, vWind);

	this->rocket_hSpeed += (hEnginesForce + hWind) * elapsedTime.asSeconds() * this->problemSpeed;
	this->rocket_vSpeed += (vEnginesForce + vWind - this->terrain.getGravity()) * elapsedTime.asSeconds() * this->problemSpeed;
	

	// Moving the rocket
	this->rocket_x += (this->rocket_hSpeed) * elapsedTime.asSeconds() * this->problemSpeed;
	this->rocket_y += (this->rocket_vSpeed) * elapsedTime.asSeconds() * this->problemSpeed;

	//cout << hSpeed << " / " << vSpeed << endl;

	// If rocket is out of map
	if (!this->terrain.isOnMap(this->rocket_x, this->rocket_y))
	{
		this->hasGoneMissing = true;
		cout << "Rocket has gone missing!" << endl;
	}
	else
	{
		//TODO: replace that 16 by the hitbox size
		if (this->terrain.collides(this->rocket_x, this->rocket_y, 22))
		{
			// If is on flat zone
			float flat1, flat2;
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
	
}

// Checks for user input
void ProblemRocket::checkEvents(sf::RenderWindow* window)
{
	if (window != NULL)
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			handleEvent(window, event);
		}
	}
}

bool ProblemRocket::handleEvent(sf::RenderWindow * window, sf::Event event)
{
	if (Problem::handleEvent(window, event))
		return true;
	else
	{
		string temp;
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			switch (event.key.code)
			{
			case sf::Keyboard::F1:
				this->initUserControl(true);
				return true;
			case sf::Keyboard::F2:
				this->initUserControl(false);
				return true;
			case sf::Keyboard::A:
				this->useRelativeChange = toggle(this->useRelativeChange);
				return true;
			case sf::Keyboard::O:
				++this->problemSpeed;
				if (this->problemSpeed > 5)
					this->problemSpeed = 5;
				return true;
			case sf::Keyboard::I:
				--this->problemSpeed;
				if (this->problemSpeed < 1)
					this->problemSpeed = 1;
				return true;
			case sf::Keyboard::R :
				this->resetRocket();
				return true;
			case sf::Keyboard::L:
				cout << "Enter terrain to load : ";
				cin >> temp;
				this->terrain.loadTerrain(temp);
				this->resetRocket();
				return true;
			}
		}
		return false;
	}
}

// returns the given angle constrained so 0 <= angle < 360
float ProblemRocket::constrainAngle(float angle)
{
	// constrain angle
	while (angle >= 360.0)
		angle -= 360.0;
	while (angle < 0.0)
		angle += 360.0;
	return angle;
}

// Call this function only if the rocket_rotationRate > 0. Rotates the rocket from the given amount, or less if its above the rocket's rotation capabilities
float ProblemRocket::constrainAngleChange(float currentAngle, float desiredRotationChange)
{
	if (!this->useRelativeChange)
		desiredRotationChange -= currentAngle;

	if (this->rocket_rotationRate < 0)
		currentAngle += desiredRotationChange;
	else
	{
		// Rotate only of the asked amount
		if (abs(desiredRotationChange) < this->rocket_rotationRate)
			currentAngle += desiredRotationChange;
		// Rotate by the change rate
		else
		{
			if (desiredRotationChange < 0)
				currentAngle -= this->rocket_rotationRate;
			else
				currentAngle += this->rocket_rotationRate;
		}
	}

	currentAngle = this->constrainAngle(currentAngle);
	return currentAngle;
}

float ProblemRocket::constrainPower(float power)
{
	if (power < 0.0)
		return 0.0;
	else if (power > this->getPowerMax())
		return this->getPowerMax();
	else
		return power;
}

// Call this function only if the engineChangeRate > 0. Rotates the rocket from the given amount, or less if its above the rocket's rotation capabilities
float ProblemRocket::constrainPowerChange(float currentPower, float desiredPowerChange)
{
	if (!this->useRelativeChange)
		desiredPowerChange -= currentPower;

	if (this->rocket_engineChangeRate < 0)
		currentPower += desiredPowerChange;
	else
	{
		// If desiredChange is lower than the change rate, change by the asked amount
		if (abs(desiredPowerChange) < this->rocket_engineChangeRate)
			currentPower += desiredPowerChange;
		// Else, change by the change rate
		else
		{
			if (desiredPowerChange < 0.0)
				currentPower -= this->rocket_engineChangeRate;
			else
				currentPower += this->rocket_engineChangeRate;
		}
	}
	currentPower = this->constrainPower(currentPower);
	return currentPower;
}

void ProblemRocket::resetDesiredChanges()
{
	for (vector<float>::iterator it = this->desiredPower.begin(); it != this->desiredPower.end(); ++it)
	{
		*it = 0;
	}
	for (vector<float>::iterator it = this->powerChange.begin(); it != this->powerChange.end(); ++it)
	{
		*it = 0;
	}
	this->desiredRotation = 0;
}

ProblemRocket::ProblemRocket(float waveAmplLossPerSec, bool useAttenuation) : Problem(waveAmplLossPerSec, useAttenuation), userControlled(false), rocket_rotationRate(-1), rocket_engineChangeRate(-1), useRelativeChange(false), problemSpeed(3)
{
	// Setting base variables
	this->rocket_x = 0;
	this->rocket_y = 0;
	this->rocket_hSpeed = 0;
	this->rocket_vSpeed = 0;
	this->desiredRotation = 0;
	this->hasCrashed = false;
	this->hasGoneMissing = false;
	this->hasLanded = false;
	this->numberOfEmitters = 0;
	this->numberOfReceptors = 0;

	this->rotationChange = 0;

	this->setAngle(0);
	this->wave_amplitude_offset = 10.0f;
	this->wave_amplitude_range = 10.0f;
	this->wave_frequency_offset = 10.0f;
	this->wave_frequency_range = 10.0f;
}

void ProblemRocket::run(sf::Time elapsedTime)
{
	if (this->pause)
		return;
	else if (!hasLanded && !hasCrashed && !hasGoneMissing && this->problemLive)
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

void ProblemRocket::clean()
{
	
}

// Resets rocket to start position
void ProblemRocket::resetRocket()
{
	this->terrain.getRocketStart(this->rocket_x, this->rocket_y, this->rocket_hSpeed, this->rocket_vSpeed, this->rocket_angle);

	this->pause = true;
	this->problemLive = true;
	this->hasCrashed = false;
	this->hasGoneMissing = false;
	this->hasLanded = false;

	for (vector<float>::iterator it = this->rocket_enginesPower.begin(); it != this->rocket_enginesPower.end(); ++it)
	{
		*it = 0.0f;
	}
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
	path += PATH_RES;
	path += "Rocket.png";
	if (!this->hud_rocketTexture.loadFromFile(path))
	{
		std::cout << "ProblemRocket::init : ERROR : couldn't load rocket image from disk." << std::endl;
	}
	this->hud_rocketSprite.setTexture(hud_rocketTexture);
	this->hud_rocketSprite.setOrigin(hud_rocketTexture.getSize().x / 2, hud_rocketTexture.getSize().y / 2);
}

void ProblemRocket::setRocketRotationRate(float rocketRotationRate)
{
	if (rocketRotationRate < 0)
		rocketRotationRate = -1;
	this->rocket_rotationRate = rocketRotationRate;
}

void ProblemRocket::setRocketengineChangeRate(float engineChangeRate)
{
	if (engineChangeRate < 0)
		engineChangeRate = -1;
	this->rocket_engineChangeRate = engineChangeRate;
}

void ProblemRocket::draw(sf::RenderWindow * window)
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

	// pause && user control
	if (this->pause)
	{
		this->hud_text.setCharacterSize(20);
		this->hud_text.setString("Pause");
		this->hud_text.setColor(sf::Color::Red);
		this->hud_text.setPosition(window->getSize().x / 2 - this->hud_text.getLocalBounds().width / 2 - 10, 35);
		window->draw(this->hud_text);
	}
	if (this->userControlled)
	{
		this->hud_text.setCharacterSize(20);
		this->hud_text.setString("User control : on");
		this->hud_text.setColor(sf::Color::Red);
		this->hud_text.setPosition(window->getSize().x / 2 - this->hud_text.getLocalBounds().width / 2 - 10, 50);
		window->draw(this->hud_text);
	}

	//speed
	this->hud_text.setColor(sf::Color::White);
	this->hud_text.setCharacterSize(20);
	temp = std::to_string(this->problemSpeed);
	this->hud_text.setString("Speed x" + temp);
	this->hud_text.setPosition(window->getSize().x - this->hud_text.getLocalBounds().width - 10, 5);
	window->draw(this->hud_text);

	//Rocket data
	this->hud_text.setCharacterSize(20);
	this->hud_text.setPosition(10, 5);
	if (this->useRelativeChange)
		this->hud_text.setString("Relative angles");
	else
		this->hud_text.setString("Fixed angles");
	window->draw(this->hud_text);

	temp = std::to_string(this->rocket_angle - PROBLEMROCKET_GUI_ANGLE_OFFSET);
	this->hud_text.setPosition(10, 25);
	this->hud_text.setString("Angle  : " + temp);
	window->draw(this->hud_text);

	temp = std::to_string(this->rocket_hSpeed);
	this->hud_text.setPosition(10, 45);
	this->hud_text.setString("hSpeed : " + temp);
	window->draw(this->hud_text);

	temp = std::to_string(this->rocket_vSpeed);
	this->hud_text.setPosition(10, 65);
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

void ProblemRocket::setPower(int engineNumber, float power)
{
	if (engineNumber >= 0 && engineNumber < this->rocket_enginesPower.size())
	{
		if (power > PROBLEMROCKET_ROCKET_POWER_MAX)
			power = PROBLEMROCKET_ROCKET_POWER_MAX;
		else if (power < 0.0)
			power = 0.0;
		this->rocket_enginesPower.at(engineNumber) = power;
	}
}

void ProblemRocket::setAngle(float angle)
{
	angle += PROBLEMROCKET_GUI_ANGLE_OFFSET;	// Applying offset to have 0° be up
	angle = constrainAngle(angle);

	this->rocket_angle = angle;
}

bool ProblemRocket::getUseRelativeChange()
{
	return this->useRelativeChange;
}

void ProblemRocket::setUseRelativeChange(bool relativeChange)
{
	this->useRelativeChange = relativeChange;
}

bool ProblemRocket::getUserControlled()
{
	return this->userControlled;
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

void ProblemRocket::getRocketPosition(float & rocketX, float & rocketY)
{
	rocketX = this->rocket_x;
	rocketY = this->rocket_y;
}

void ProblemRocket::getRocketSpeed(float & rocketHSpeed, float & rocketVSpeed)
{
	rocketHSpeed = this->rocket_hSpeed;
	rocketVSpeed = this->rocket_vSpeed;
}

float ProblemRocket::getRocketAngle()
{
	return this->rocket_angle;
}

vector<float>* ProblemRocket::getRocketEnginesPower()
{
	return &this->rocket_enginesPower;
}

float ProblemRocket::getRocketDistanceToGround()
{
	
	return (this->rocket_y - this->terrain.getTerrainPoint(this->rocket_x));
}

float ProblemRocket::getRocketDistanceToLandingZoneCenter()
{
	float flat1, flat2;
	this->terrain.getLandingZone(flat1, flat2);
	float center = flat1 + (flat2 - flat1) / 2;
	return center - this->rocket_x;
}

float ProblemRocket::getLandingZoneSize()
{
	float landing1, landing2;
	this->terrain.getLandingZone(landing1, landing2);
	return landing2 - landing1;
}

float ProblemRocket::getPowerMax()
{
	return 100.0;
}

void ProblemRocket::getHighestPointBeforeLanding(float & pointX, float & pointY)
{
	this->terrain.getHighestPointBeforeLandingZone(this->rocket_x, this->rocket_y, pointX, pointY);
}

void ProblemRocket::getSafeLandingSpecs(float & maxHSpeed, float & maxVSpeed, float & maxAngle)
{
	maxHSpeed = 20.0f;
	maxVSpeed = 40.0f;
	maxAngle = 10.0f;
}

// Sets the power influence
void ProblemRocket::setDesiredPower(int engineNumber, float power)
{
	if (engineNumber >= 0 && engineNumber < this->desiredPower.size())
		this->desiredPower.at(engineNumber) = power;
	else
		cout << "ERROR : ProblemRocket::setDesiredPower : given engine number is out of range" << endl;
}

// Sets the angle influence
void ProblemRocket::setDesiredAngle(float angle)
{
	this->desiredRotation = angle;
}

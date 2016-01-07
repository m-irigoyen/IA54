#include "ProblemRocket.h"

/*
Checks if the rocket landed correctly.
We assume that a correct landing means :
|hSpeed| < 20
|vSpeed| < 40
-10 <= rocketAngle <= 10
*/
bool ProblemRocket::correctLanding(float hSpeed, float vSpeed, float angle)
{
	// Don't forget to check for the angle offset
	// Checking angle
	if (angle <= (PROBLEMROCKET_GUI_ANGLE_OFFSET + this->getMaxAngle())
		&& angle >= (PROBLEMROCKET_GUI_ANGLE_OFFSET - this->getMaxAngle()))
	{
		if (abs(hSpeed) <= this->getMaxHSpeed())
		{
			if (abs(vSpeed) <= this->getMaxVSpeed())
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
		this->problemLive = false;
		cout << "Rocket has gone missing!" << endl;
	}
	else
	{
		if (this->terrain.collides(this->rocket_x, this->rocket_y, PROBLEMROCKET_ROCKET_HITBOX))
		{
			// If is on flat zone
			float flat1, flat2;
			this->terrain.getLandingZone(flat1, flat2);
			if (this->rocket_x >= flat1 && rocket_x <= flat2)
			{
				if (this->correctLanding(this->rocket_hSpeed, this->rocket_vSpeed, this->rocket_angle))
				{
					this->hasLanded = true;
					this->trajectories.sucessfulTrajectory();
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
		float xWorld, yWorld;
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			switch (event.key.code)
			{
			case sf::Keyboard::U:
				toggle(this->userControlled);
				this->initUserControl(this->userControlled);
				return true;
			case sf::Keyboard::A:
				this->useRelativeChange = toggle(this->useRelativeChange);
				return true;
			case sf::Keyboard::Add:
				++this->problemSpeed;
				if (this->problemSpeed > 20)
					this->problemSpeed = 20;
				return true;
			case sf::Keyboard::Subtract:
				--this->problemSpeed;
				if (this->problemSpeed < 1)
					this->problemSpeed = 1;
				return true;
			case sf::Keyboard::R :
				this->resetRocket();
				return true;
			case sf::Keyboard::L:
				cout << "Enter the name of the terrain to load : ";
				cin >> temp;
				this->loadTerrain(temp);
				return true;
			case sf::Keyboard::Tab :
				toggle(this->drawHUD);
				return true;
			case sf::Keyboard::T:
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)
					|| sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
					this->trajectories.clearLast();
				else
					this->trajectories.clear();
				return true;

				//Rocket shortcuts
			case sf::Keyboard::F5:
				this->loadTerrain("VelocityH");
				return true;
			case sf::Keyboard::F6:
				this->loadTerrain("VelocityV");
				return true;
			case sf::Keyboard::F7:
				this->loadTerrain("Mountain");
				return true;
			case sf::Keyboard::F8:
				this->loadTerrain("Plateau");
				return true;
			case sf::Keyboard::F9:
				this->loadTerrain("DoubleBack");
				return true;
			case sf::Keyboard::F10:
				this->loadTerrain("Pit");
				return true;
			case sf::Keyboard::F11:
				this->loadTerrain("DoublePit");
				return true;
			case sf::Keyboard::F12:
				this->loadTerrain("PrecisionLanding");
				return true;
			}
			break;
			
		case sf::Event::MouseButtonPressed : 
			switch (event.mouseButton.button)
			{
			case sf::Mouse::Left:
				// If ctrl is pressed, set start position
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)
					|| sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
				{
					this->terrain.getWorldCoordinates((float)event.mouseButton.x, (float)event.mouseButton.y, window, xWorld, yWorld);
					this->rocket_x = xWorld;
					this->rocket_y = yWorld;
				}
				return true;
			}
			break;
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

	if (this->rocket_rotationRate < 0.0f)
		currentAngle += desiredRotationChange;
	else
	{
		// Rotate only of the asked amount
		if (abs(desiredRotationChange) < this->rocket_rotationRate*this->problemSpeed)
			currentAngle += desiredRotationChange;
		// Rotate by the change rate
		else
		{
			if (desiredRotationChange < 0)
				currentAngle -= this->rocket_rotationRate*this->problemSpeed;
			else
				currentAngle += this->rocket_rotationRate*this->problemSpeed;
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
		if (abs(desiredPowerChange) < this->rocket_engineChangeRate * this->problemSpeed)
			currentPower += desiredPowerChange;
		// Else, change by the change rate
		else
		{
			if (desiredPowerChange < 0.0)
				currentPower -= this->rocket_engineChangeRate * this->problemSpeed;
			else
				currentPower += this->rocket_engineChangeRate * this->problemSpeed;
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

void ProblemRocket::setHasCrashed(bool crashed)
{
	if (crashed)
	{
		this->hasCrashed = true;
		this->problemLive = false;
	}
}

void ProblemRocket::setHasLanded(bool landed)
{
	if (landed)
	{
		this->hasLanded= true;
		this->problemLive = false;
	}
}

void ProblemRocket::setHasGoneMissing(bool goneMissing)
{
	if (goneMissing)
	{
		this->hasGoneMissing = true;
		this->problemLive = false;
	}
}

void ProblemRocket::resetScale()
{
	this->hud_rocketSprite.setScale(PROBLEMROCKET_GUI_SCALE / getScale(PROBLEMROCKET_TERRAIN_DEFAULTSIZE, this->terrain.getWidth()), PROBLEMROCKET_GUI_SCALE / getScale(PROBLEMROCKET_TERRAIN_DEFAULTSIZE, this->terrain.getHeight()));
	this->hud_explosionSprite.setScale(PROBLEMROCKET_GUI_SCALE / getScale(PROBLEMROCKET_TERRAIN_DEFAULTSIZE, this->terrain.getWidth()), PROBLEMROCKET_GUI_SCALE / getScale(PROBLEMROCKET_TERRAIN_DEFAULTSIZE, this->terrain.getHeight()));
	this->hud_radarSprite.setScale(0.2f / getScale(PROBLEMROCKET_TERRAIN_DEFAULTSIZE, this->terrain.getWidth()), 0.2f / getScale(PROBLEMROCKET_TERRAIN_DEFAULTSIZE, this->terrain.getHeight()));
}

ProblemRocket::ProblemRocket(float waveAmplLossPerSec, bool useAttenuation) : Problem(waveAmplLossPerSec, useAttenuation), userControlled(false), rocket_rotationRate(0.1f), rocket_engineChangeRate(0.1f), useRelativeChange(false), problemSpeed(5), problemMaxAngle(0.0f), problemMaxHSpeed(0.0f), problemMaxVSpeed(0.0f), desiredAltitude(0.0f), drawHUD(true)
{
	// Initializing agent count
	this->agentCount.insert(pair<int, int>(0, 0));
	this->agentCount.insert(pair<int, int>(1, 0));
	this->agentCount.insert(pair<int, int>(2, 0));
	this->agentCount.insert(pair<int, int>(3, 0));
	this->agentCount.insert(pair<int, int>(4, 0));
	this->agentCount.insert(pair<int, int>(5, 0));
	this->agentCount.insert(pair<int, int>(6, 0));

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

		// Trajectory
		this->trajectories.inputTrajectory(this->rocket_x, this->rocket_y);
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
	float rocketStartPower;
	this->terrain.getRocketStart(this->rocket_x, this->rocket_y, this->rocket_hSpeed, this->rocket_vSpeed, this->rocket_angle, rocketStartPower);

	this->pause = true;
	this->problemLive = true;
	this->hasCrashed = false;
	this->hasGoneMissing = false;
	this->hasLanded = false;
	this->resetAgents = true;

	for (vector<float>::iterator it = this->rocket_enginesPower.begin(); it != this->rocket_enginesPower.end(); ++it)
	{
		*it = 0.0f;
	}
	this->initRocketStartPower(rocketStartPower);

	this->trajectories.prepareNewTrajectory();
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
	if (!this->hud_rocketTexture.loadFromFile(PATH_RES + "Rocket.png"))
	{
		std::cout << "ProblemRocket::init : ERROR : couldn't load rocket image from disk." << std::endl;
	}
	this->hud_rocketSprite.setTexture(hud_rocketTexture);
	this->hud_rocketSprite.setOrigin(hud_rocketTexture.getSize().x / 2, hud_rocketTexture.getSize().y *  2/3);

	// Explosion sprite
	if (!this->hud_explosionTexture.loadFromFile(PATH_RES + "Explosion.png"))
	{
		std::cout << "ProblemRocket::init : ERROR : couldn't load explosion image from disk." << std::endl;
	}
	this->hud_explosionSprite.setTexture(this->hud_explosionTexture);
	this->hud_explosionSprite.setOrigin(hud_explosionTexture.getSize().x / 2, hud_explosionTexture.getSize().y * 2 / 3);

	// Radar sprite
	if (!this->hud_radarTexture.loadFromFile(PATH_RES + "RadarMissing.png"))
	{
		std::cout << "ProblemRocket::init : ERROR : couldn't load explosion image from disk." << std::endl;
	}
	this->hud_radarSprite.setTexture(this->hud_radarTexture);
	this->hud_radarSprite.setOrigin(hud_radarTexture.getSize().x / 2, hud_radarTexture.getSize().y * 2 / 3);

	this->resetScale();
}

void ProblemRocket::setRocketRotationRate(float rocketRotationRate)
{
	if (rocketRotationRate < 0.0f)
		rocketRotationRate = -1.0f;
	this->rocket_rotationRate = rocketRotationRate;
}

void ProblemRocket::setRocketengineChangeRate(float engineChangeRate)
{
	if (engineChangeRate < 0.0f)
		engineChangeRate = -1.0f;
	this->rocket_engineChangeRate = engineChangeRate;
}

void ProblemRocket::draw(sf::RenderWindow * window)
{
	this->checkEvents(window);

	// Drawing terrain
	this->terrain.draw(window);

	// Drawing trajectories 
	this->trajectories.drawAll(window, this->terrain.getWidth(), this->terrain.getHeight());

	// Drawing rocket
	float convX, convY;
	convertCoordinates(this->rocket_x, this->rocket_y, this->terrain.getWidth(), this->terrain.getHeight(), convX, convY, window->getSize().x, window->getSize().y);
	if (this->problemLive || this->hasLanded)
	{
		this->hud_rocketSprite.setPosition(convX, window->getSize().y - convY);
		this->hud_rocketSprite.setRotation(-this->rocket_angle + 90);
		window->draw(this->hud_rocketSprite);
	}
	else if (this->hasCrashed)
	{
		this->hud_explosionSprite.setPosition(convX, window->getSize().y - convY);
		this->hud_explosionSprite.setRotation(-this->rocket_angle + 90);
		window->draw(this->hud_explosionSprite);
	}
	else if (this->hasGoneMissing)
	{
		this->hud_radarSprite.setPosition(convX, window->getSize().y - convY);
		window->draw(this->hud_radarSprite);
	}


	if (this->drawHUD)
	{
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
		if (abs(this->rocket_angle - PROBLEMROCKET_GUI_ANGLE_OFFSET) > PROBLEMROCKET_LANDING_MAXANGLE)
			this->hud_text.setColor(sf::Color::Red);
		else
			this->hud_text.setColor(sf::Color::Green);
		this->hud_text.setPosition(10, 25);
		this->hud_text.setString("Angle  : " + temp);
		window->draw(this->hud_text);

		temp = std::to_string(this->rocket_hSpeed);
		if (abs(this->rocket_hSpeed) > PROBLEMROCKET_LANDING_MAXHSPEED)
			this->hud_text.setColor(sf::Color::Red);
		else
			this->hud_text.setColor(sf::Color::Green);
		this->hud_text.setPosition(10, 45);
		this->hud_text.setString("hSpeed : " + temp);
		window->draw(this->hud_text);

		temp = std::to_string(this->rocket_vSpeed);
		if (abs(this->rocket_vSpeed) > PROBLEMROCKET_LANDING_MAXVSPEED)
			this->hud_text.setColor(sf::Color::Red);
		else
			this->hud_text.setColor(sf::Color::Green);
		this->hud_text.setPosition(10, 65);
		this->hud_text.setString("vSpeed : " + temp);
		window->draw(this->hud_text);

		this->hud_text.setColor(sf::Color::White);
		// Engine values must be drawned in other classes
	}
}

void ProblemRocket::loadTerrain(string path)
{
	this->terrain.loadTerrain(path);
	this->resetRocket();
	this->trajectories.clear();
	this->resetScale();
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

float ProblemRocket::getDesiredAltitude()
{
	return this->desiredAltitude;
}

void ProblemRocket::setDesiredAltitude(float altitude)
{
	this->desiredAltitude = altitude;
}

bool ProblemRocket::getUserControlled()
{
	return this->userControlled;
}

ProblemRocket_Terrain * ProblemRocket::getTerrain()
{
	return &this->terrain;
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
	maxHSpeed = this->getMaxHSpeed();
	maxVSpeed = this->getMaxVSpeed();
	maxAngle = this->getMaxAngle();
}

float ProblemRocket::getMaxHSpeed()
{
	return this->problemMaxHSpeed;
}

float ProblemRocket::getMaxVSpeed()
{
	return this->problemMaxVSpeed;
}

float ProblemRocket::getMaxAngle()
{
	return this->problemMaxAngle;
}

void ProblemRocket::setMaxHSpeed(float maxHSpeed)
{

	this->problemMaxHSpeed = abs(maxHSpeed);
}

void ProblemRocket::setMaxVSpeed(float maxVSpeed)
{
	this->problemMaxVSpeed = abs(maxVSpeed);
}

void ProblemRocket::setMaxAngle(float maxAngle)
{
	this->problemMaxAngle = abs(maxAngle);
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

void ProblemRocket::addedAgent(int agentType)
{
	this->agentCount.at(agentType) += 1;
	switch (agentType)
	{
	case 0 :
		this->numberOfReceptors++;
		break;
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
		this->numberOfEmitters++;
		break;
	}
}

void ProblemRocket::removedAgent(int agentType)
{
	this->agentCount.at(agentType) -= 1;
	if (this->agentCount.at(agentType) < 0)
		this->agentCount.at(agentType) = 0;
	
	switch (agentType)
	{
	case 0:
		this->numberOfReceptors--;
		break;
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
		this->numberOfEmitters--;
		break;
	}

	if (this->numberOfEmitters < 0)
		this->numberOfEmitters = 0;
	if (this->numberOfReceptors < 0)
		this->numberOfReceptors = 0;
}

map<int, int>& ProblemRocket::getAgentCount()
{
	return this->agentCount;
}

bool ProblemRocket::checkCorrectLanding(float x, float y, float hSpeed, float vSpeed, float angle)
{
	// Checking if this is in the landing zone
	float distanceToCenterFlat = this->getRocketDistanceToLandingZoneCenter();	// Rocket distance to center of the landing zone
	float lzSize = this->getLandingZoneSize();	// Landing zone size (width)
	if (abs(distanceToCenterFlat) < lzSize/2)
	{
		// Checking if angle is correct
		if (abs(angle) <= this->getMaxAngle())	// Don't forget to check for the angle offset
		{
			// Correct hSpeed
			if (abs(hSpeed) <= this->getMaxHSpeed())
			{
				//Correct vSpeed
				if (abs(vSpeed) <= this->getMaxVSpeed())
				{
					return true;
				}
			}
		}
	}
	return false;
}

float ProblemRocket::getPowerOffset()
{
	return this->problemPowerOffset;
}

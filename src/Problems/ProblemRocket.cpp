#include "ProblemRocket.h"


ProblemRocket::ProblemRocket() : Problem(), worldWidth(SIZE_DEFAULT_WIDTH), worldHeight(SIZE_DEFAULT_HEIGHT), rocketX(worldWidth/2), rocketY(worldHeight/2), hasLanded(false), hasCrashed(false), hSpeed(0.0), vSpeed(0.0), enginePower(0), userControlled(true)
{
	this->setAngle(0);
	this->loadTerrain();
}

void ProblemRocket::resetRocket(int x, int y)
{
	if (x == -1 || y == -1)
	{
		this->rocketX = this->worldWidth / 2;
		this->rocketY = this->worldHeight/ 2;
	}

	this->setAngle(0);
	this->enginePower = 0;
	this->hSpeed = 0;
	this->vSpeed = 0;
}

//Check if rocket collides with the ground
bool ProblemRocket::collides(double x, double y)
{
	if (x <= 0 || y <= 0 || x >= this->worldWidth || y >= this->worldHeight)
	{
		cout << "Rocket went missing!" << endl;
		this->hasCrashed = true;
		return true;
	}

	pair<int, int> p1, p2;

	p1 = *this->terrain.begin();
		
	//TODO : replace by a call to getPointBefore
	bool collides = false;
	for (vector<pair<int, int>>::iterator it = this->terrain.begin()+1; it != this->terrain.end(); ++it)
	{
		p2 = *it;
		// Found the englobing points
		if (p2.first >= x)
		{

		}
	}
	

	// First : check if the position collides with terrain
	if (y <= 0.0)
	{
		// Second : check if the speed and angle is correct
		return true;
	}
	else
		return false;
}

/*
Checks if the rocket landed correctly.
We assume that a correct landing means : 
|hSpeed| < 20
|vSpeed| < 40
-5 <= rocketAngle <= 5
*/
bool ProblemRocket::correctLanding(double hSpeed, double vSpeed, double angle)
{
	if (angle >= ANGLE_OFFSET-10 && angle <= ANGLE_OFFSET + 10)	// Don't forget to check for the angle offset
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

int ProblemRocket::getTerrainPoint(double x, pair<int, int> p1, pair<int, int> p2)
{
	int x1, y1, x2, y2;
	x1 = p1.first;
	y1 = p1.second;
	x2 = p2.first;
	y2 = p2.second;

	int distanceP1P2 = p2.first - p1.first;
	double distanceP1X = x - p1.first;

	double distRatio = distanceP1X / distanceP1P2;


//	y = 

	cout << "p1 : " << x1 << "," << y1 << endl;
	cout << "p2 : " << x2 << "," << y2 << endl;
	cout << "x : " << x << endl;

	return 0;
}

vector<pair<int, int>>::iterator ProblemRocket::getPointBefore(double x)
{
	if (this->terrain.size() < 2)
	{
		cout << "ProblemRocket::getPointBefore : ERROR : Terrain is invalid as it contains less than 2 terrain points" << endl;
		return this->terrain.end();
	}
		
	pair<int, int> p = *this->terrain.begin();
	for (vector<pair<int, int>>::iterator it = this->terrain.begin() + 1; it != this->terrain.end(); ++it)
	{
		if (it->first > x)
			return it-1;
	}

	cout << "ProblemRocket::getPointBefore : ERROR : Didn't find a point before for given x." << endl;
	return this->terrain.end();
}

void ProblemRocket::getThrustersForce(double angle, int power, double & horizontalForce, double & verticalForce)
{
	double vecX = cos(degToRad(angle));
	double vecY = sin(degToRad(angle));

	//cout << "Thruster computation : " << vecX << "," << vecY << endl;

	horizontalForce = (power*THRUSTER_STRENGTH*vecX) / 100;
	verticalForce = (power*THRUSTER_STRENGTH*vecY) / 100;

	//cout << "V : " << verticalForce << endl;
}

void ProblemRocket::checkEvents(sf::RenderWindow * window)
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed :
			window->close();
			return;
		case sf::Event::KeyPressed:
			switch (event.key.code)
			{
			case::sf::Keyboard::F1:
				this->userControlled = true;
				break;
			case::sf::Keyboard::F2:
				this->userControlled = false;
				break;
			case::sf::Keyboard::Escape:
				window->close();
				break;
			}
		}
	}

	// Engine control
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (this->userControlled)
			this->addPower(1);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (this->userControlled)
			this->addPower(-1);
	}

	// Angle control
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (this->userControlled)
			this->addAngle(-1);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if (this->userControlled)
			this->addAngle(1);
	}
}

void ProblemRocket::loadTerrain(std::string path)
{
	if (path.compare("Default") == 0)
	{
		cout << "ProblemRocket::loadTerrain : Loading default terrain" << endl;
		// Loading default terrain
		this->terrain.push_back(pair<int, int>(0, 400));
		this->terrain.push_back(pair<int, int>(800, 100));
		this->terrain.push_back(pair<int, int>(2000, 1500));
		this->terrain.push_back(pair<int, int>(2500, 1400));
		this->terrain.push_back(pair<int, int>(2700, 50));
		this->terrain.push_back(pair<int, int>(3700, 50));
		this->terrain.push_back(pair<int, int>(8000, 200));

		this->worldWidth = 8000;
		this->worldHeight = 8000;

		this->resetRocket();
	}
}

void ProblemRocket::run(sf::Time elapsedTime)
{
	if (!hasLanded && !hasCrashed)
	{
		if (!this->userControlled)
		{
			// Adding agent's influence
			this->addAngle(this->desiredRotationChange);
			this->addPower(this->desiredPowerChange);

			this->desiredPowerChange = 0;
			this->desiredRotationChange = 0;
		}

		double hOffset, vOffset;
		getThrustersForce(this->rocketAngle, this->enginePower, hOffset, vOffset);

		hSpeed += hOffset * elapsedTime.asSeconds();
		vSpeed += vOffset * elapsedTime.asSeconds() - (MARS_GRAVITY*elapsedTime.asSeconds());

		this->rocketY += vSpeed * elapsedTime.asSeconds();
		this->rocketX += hSpeed * elapsedTime.asSeconds();

		//cout << hSpeed << " / " << vSpeed << endl;

		// If collides with terrain
		if (this->collides(rocketX, rocketY))
		{
			// If is on flat zone
			if (1)
			{
				if (this->correctLanding(hSpeed, vSpeed, rocketAngle))
					this->hasLanded = true;
				else
					this->hasCrashed = true;
			}
			else
				this->hasCrashed = true;
		}
	}
	else
	{
		
	}
}

// Draw the problem
void ProblemRocket::draw(sf::RenderWindow * problemWindow, std::vector<sf::Font>* fonts)
{
	this->checkEvents(problemWindow);

	// Drawing terrain
	//TODO: draw the terrain

	// Drawing engine fire
	if (this->enginePower > 0)
	{
		this->hud_engineFire.setSize(sf::Vector2f(this->enginePower*HUD_SIZE_THRUSTER, 6));
		this->hud_engineFire.setOrigin(this->enginePower*HUD_SIZE_THRUSTER + this->hud_rocketSprite.getLocalBounds().width/2, 3);
		this->hud_engineFire.setRotation(-this->rocketAngle);
		this->hud_engineFire.setPosition(rocketX*problemWindow->getSize().x / worldWidth,
			problemWindow->getSize().y - (rocketY*problemWindow->getSize().y / worldHeight));

		problemWindow->draw(this->hud_engineFire);
	}

	// Drawing terrain
	if (!this->terrain.empty())
	{

	}	

	// Drawing rocket
	this->hud_rocketSprite.setPosition(rocketX*problemWindow->getSize().x / worldWidth,
		problemWindow->getSize().y - (rocketY*problemWindow->getSize().y / worldHeight));
	this->hud_rocketSprite.setRotation(-this->rocketAngle);

	problemWindow->draw(this->hud_rocketSprite);

	// Drawing HUD
	string temp;
	temp = std::to_string(this->rocketAngle - ANGLE_OFFSET);
	this->hud_angle.setString("Angle  : " + temp);

	temp = std::to_string(this->hSpeed);
	this->hud_hSpeed.setString("hSpeed : " + temp);

	temp = std::to_string(this->vSpeed);
	this->hud_vSpeed.setString("vSpeed : " + temp);

	temp = std::to_string(this->enginePower);
	this->hud_power.setString("Power  : " + temp);

	problemWindow->draw(this->hud_angle);
	problemWindow->draw(this->hud_hSpeed);
	problemWindow->draw(this->hud_vSpeed);
	problemWindow->draw(this->hud_power);
}

void ProblemRocket::init()
{
	//TODO: load rocket image and set sprite
	
}

void ProblemRocket::initGraphics(std::vector<sf::Font>* fonts)
{
	// Text
	this->hud_angle.setFont(fonts->at(0));
	this->hud_angle.setCharacterSize(20);
	this->hud_angle.setPosition(10, 5);
	this->hud_angle.setColor(sf::Color::White);

	this->hud_power.setFont(fonts->at(0));
	this->hud_power.setCharacterSize(20);
	this->hud_power.setPosition(10, 25);
	this->hud_power.setColor(sf::Color::White);

	this->hud_vSpeed.setFont(fonts->at(0));
	this->hud_vSpeed.setCharacterSize(20);
	this->hud_vSpeed.setPosition(10, 45);
	this->hud_vSpeed.setColor(sf::Color::White);

	this->hud_hSpeed.setFont(fonts->at(0));
	this->hud_hSpeed.setCharacterSize(20);
	this->hud_hSpeed.setPosition(10, 65);
	this->hud_hSpeed.setColor(sf::Color::White);

	// Rocket sprite
	if (!this->hud_rocketTexture.loadFromFile("../Project/res/Rocket.png"))
	{
		std::cout << "ProblemRocket::init : ERROR : couldn't load rocket image from disk." << std::endl;
	}
	this->hud_rocketSprite.setTexture(hud_rocketTexture);
	this->hud_rocketSprite.setOrigin(hud_rocketTexture.getSize().x / 2, hud_rocketTexture.getSize().y / 2);

	// Engine fire
	this->hud_engineFire.setFillColor(sf::Color::Yellow);
	this->hud_engineFire.setOutlineColor(sf::Color::Red);
	this->hud_engineFire.setOutlineThickness(1);
	this->hud_engineFire.setSize(sf::Vector2f(50,6));
	this->hud_engineFire.setOrigin(0, 3);
}

void ProblemRocket::setPower(int power)
{
	if (power > 100)
		power = 100;
	else if (power < 0)
		power = 0;
	this->enginePower = power;
}

void ProblemRocket::addPower(int powerOffset)
{
	this->setPower(this->enginePower + powerOffset);
}

void ProblemRocket::setAngle(double angle)
{
	angle += ANGLE_OFFSET;	// Applying offset to have 0° be up
	while (angle >= 360)
		angle -= 360;
	while (angle < 0)
		angle += 360;
		
	this->rocketAngle = angle;
}

void ProblemRocket::addAngle(double angleOffset)
{
	this->setAngle(this->rocketAngle-ANGLE_OFFSET + angleOffset);
	//cout << "Adding angle" << endl;
}

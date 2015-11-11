#include "Problems/Rocket/HardSet/OneEngine/ProblemRocket_HS_OneEngine.h"


ProblemRocket_HS_OneEngine::ProblemRocket_HS_OneEngine(float waveAmplLossPerSec) : Problem(waveAmplLossPerSec), worldWidth(SIZE_DEFAULT_WIDTH), worldHeight(SIZE_DEFAULT_HEIGHT), rocketX(worldWidth/2), rocketY(worldHeight/2), hasLanded(false), hasCrashed(false), hSpeed(0.0), vSpeed(0.0), enginePower(0), userControlled(true), desiredPowerChange(0), desiredRotationChange(0)
{
	this->setAngle(0);
	this->loadTerrain();
}

void ProblemRocket_HS_OneEngine::resetRocket(int x, int y)
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
bool ProblemRocket_HS_OneEngine::collides(double x, double y)
{
	
}

/*
Checks if the rocket landed correctly.
We assume that a correct landing means : 
|hSpeed| < 20
|vSpeed| < 40
-5 <= rocketAngle <= 5
*/
bool ProblemRocket_HS_OneEngine::correctLanding(double hSpeed, double vSpeed, double angle)
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


void ProblemRocket_HS_OneEngine::getThrustersForce(double angle, int power, double & horizontalForce, double & verticalForce)
{
	double vecX = cos(degToRad(angle));
	double vecY = sin(degToRad(angle));

	//cout << "Thruster computation : " << vecX << "," << vecY << endl;

	horizontalForce = (power*THRUSTER_STRENGTH*vecX) / 100;
	verticalForce = (power*THRUSTER_STRENGTH*vecY) / 100;

	//cout << "V : " << verticalForce << endl;
}

void ProblemRocket_HS_OneEngine::checkEvents(sf::RenderWindow * window)
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

double ProblemRocket_HS_OneEngine::constrainAngle(double angle)
{
	// constrain angle
	while (angle >= 360)
		angle -= 360;
	while (angle < 0)
		angle += 360;
	return angle;
}

void ProblemRocket_HS_OneEngine::loadTerrain(std::string path)
{
	this->terrain.clear();
	this->worldFlatZone1 = -1;
	this->worldFlatZone2 = -1;
	this->worldWidth = -1;
	this->worldHeight = -1;

	if (path.compare("Default") == 0)
	{
		cout << "ProblemRocket::loadTerrain : Loading default terrain" << endl;
		// Loading default terrain
		this->terrain.push_back(pair<int, int>(0, 600));
		this->terrain.push_back(pair<int, int>(100, 500));
		this->terrain.push_back(pair<int, int>(200, 200));
		this->terrain.push_back(pair<int, int>(250, 275));
		this->terrain.push_back(pair<int, int>(265, 275));
		this->terrain.push_back(pair<int, int>(300, 100));
		this->terrain.push_back(pair<int, int>(325, 110));
		this->terrain.push_back(pair<int, int>(370, 420));
		this->terrain.push_back(pair<int, int>(380, 430));
		this->terrain.push_back(pair<int, int>(400, 250));
		this->terrain.push_back(pair<int, int>(500, 100));
		this->terrain.push_back(pair<int, int>(800, 100));
		this->terrain.push_back(pair<int, int>(1000, 200));

		this->worldWidth = 1000;
		this->worldHeight = 1000;
		this->worldFlatZone1 = 500;
		this->worldFlatZone2 = 800;
	}
	else
	{
		string filePath = "../Project/res/";
		filePath += path;

		// XML document creation
		pugi::xml_document doc;

		// Load document
		pugi::xml_parse_result result = doc.load_file(filePath.data());
		if (result.status != pugi::xml_parse_status::status_ok)
		{
			// An error occured
			std::cout << "ERROR : ProblemRocket::loadTerrain : unable to parse given file : " << filePath << std::endl;
			std::cout << "Aborting terrain loading..." << std::endl;
			return;
		}

		// Loading terrain dimensions
		pugi::xml_node terrainNode = doc.child("terrain");
		this->worldWidth = terrainNode.attribute("width").as_int();
		this->worldHeight = terrainNode.attribute("height").as_int();
		this->worldFlatZone1 = terrainNode.attribute("flat1").as_int();
		this->worldFlatZone2 = terrainNode.attribute("flat2").as_int();

		// Loading terrain points
		pugi::xml_node pointsNode = terrainNode.child("points");
		// iterate over genome nodes in the genomes node
		for (pugi::xml_node point : pointsNode.children())
		{
			pair<int, int> p;
			p.first = point.attribute("x").as_int();
			p.second = point.attribute("y").as_int();

			this->terrain.push_back(p);
		}
	}

	this->resetRocket();
}

void ProblemRocket_HS_OneEngine::saveTerrain(std::string path)
{
	if (path.compare("Default") == 0)
	{
		cout << "ProblemRocket::saveTerrain : ERROR save path can't be 'Default'. Aborting save" << endl;
		return;
	}
	else
	{
		cout << "ProblemRocket::saveTerrain : saving current terrain..." << endl;

		// Creating the xml doc
		pugi::xml_document doc;

		// Set XML declaration
		auto declarationNode = doc.append_child(pugi::node_declaration);
		declarationNode.append_attribute("version") = "1.0";
		declarationNode.append_attribute("encoding") = "UTF-8";
		declarationNode.append_attribute("standalone") = "yes";

		// Set XML root node
		pugi::xml_node terrainNode = doc.append_child("terrain");

		// Saving world dimensions
		terrainNode.append_attribute("width").set_value(this->worldWidth);
		terrainNode.append_attribute("height").set_value(this->worldHeight);
		terrainNode.append_attribute("flat1").set_value(this->worldFlatZone1);
		terrainNode.append_attribute("flat2").set_value(this->worldFlatZone2);

		// terrain points
		for (vector<pair<int, int>>::iterator it = this->terrain.begin(); it != this->terrain.end(); ++it)
		{
			pugi::xml_node pointNode = terrainNode.append_child("point");

			// Saving genome data
			pointNode.append_attribute("x").set_value(it->first);
			pointNode.append_attribute("y").set_value(it->second);
		}
		string filePath = "../Project/res/";
		filePath += path;
		std::cout << "Save result : " << filePath.data() << " : " << doc.save_file(filePath.data()) << std::endl;
	}
}

void ProblemRocket_HS_OneEngine::run(sf::Time elapsedTime)
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
			if (rocketX >= worldFlatZone1 && rocketX <= worldFlatZone2)
			{
				if (this->correctLanding(hSpeed, vSpeed, rocketAngle))
					this->hasLanded = true;
				else
					this->hasCrashed = true;
			}
			else
			{
				this->hasCrashed = true;
				cout << "Rocket crashed : landed on non flat zone!" << endl;
			}
				
		}
	}
	else
		this->problemLive = false;
}

// Draw the problem
void ProblemRocket_HS_OneEngine::draw(sf::RenderWindow * problemWindow, std::vector<sf::Font>* fonts)
{
	this->checkEvents(problemWindow);

	// Drawing terrain
	//TODO: draw the terrain
	// Drawing terrain
	if (!this->terrain.empty())
	{
		vector<pair<int, int>>::iterator p = this->terrain.begin();
		for (vector<pair<int, int>>::iterator it = this->terrain.begin()+1; it != this->terrain.end(); ++it)
		{
			sf::Vertex line[] =
			{
				sf::Vertex(sf::Vector2f(p->first*problemWindow->getSize().x / worldWidth, 
					(worldHeight - p->second)*problemWindow->getSize().y / worldHeight)),
				sf::Vertex(sf::Vector2f(it->first*problemWindow->getSize().x / worldWidth, 
					(worldHeight - it->second)*problemWindow->getSize().y / worldHeight))
			};

			problemWindow->draw(line, 2, sf::Lines);

			p = it;
		}
	}

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

void ProblemRocket_HS_OneEngine::clean()
{
	this->terrain.clear();
}

void ProblemRocket_HS_OneEngine::init()
{
	// Nothing to do here	
	this->rocketX = 900;
	this->rocketY = 900;
}

void ProblemRocket_HS_OneEngine::initGraphics(std::vector<sf::Font>* fonts)
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

void ProblemRocket_HS_OneEngine::setPower(int power)
{
	if (power > ROCKET_SPECS_POWER_MAX)
		power = ROCKET_SPECS_POWER_MAX;
	else if (power < 0)
		power = 0;
	this->enginePower = power;
}

void ProblemRocket_HS_OneEngine::addPower(int powerOffset)
{
	this->setPower(this->enginePower + powerOffset);
}

void ProblemRocket_HS_OneEngine::setAngle(double angle)
{
	angle += ANGLE_OFFSET;	// Applying offset to have 0° be up
	angle = constrainAngle(angle);
		
	this->rocketAngle = angle;
}

void ProblemRocket_HS_OneEngine::addAngle(double angleOffset)
{
	this->setAngle(this->rocketAngle-ANGLE_OFFSET + angleOffset);
	//cout << "Adding angle" << endl;
}

double ProblemRocket_HS_OneEngine::getAngle()
{
	double angle = this->rocketAngle;
	angle -= ANGLE_OFFSET;	// Applying offset to have 0° be up

	angle = constrainAngle(angle);

	return angle;
}

void ProblemRocket_HS_OneEngine::setNumberOfEmitters(int nb)
{
	if (nb < 0)
		nb = 0;
	this->numberOfAgents = nb;
}

int ProblemRocket_HS_OneEngine::getNumberOfEmitters()
{
	return this->numberOfAgents;
}

// Get the current rocket data
void ProblemRocket_HS_OneEngine::getProblemData(double& x, double& y, double & hSpeed, double & vSpeed, double & angle, double& power, double & distanceToGround, double & distanceToCenterOfLandingZone)
{
	hSpeed = this->hSpeed;
	vSpeed = this->vSpeed;
	angle = this->getAngle();
	power = this->enginePower;
	
	vector<pair<int, int>>::iterator p;
	p = this->getPointBefore(this->rocketX);
	if (p != this->terrain.end())
	{
		double terrainY = this->getTerrainPoint(this->rocketX, *p, *(p + 1));
		distanceToGround = this->rocketY - terrainY;
	}
	else
		distanceToGround = 0;
	
	

	distanceToCenterOfLandingZone = this->rocketX - (this->worldFlatZone2 - ((this->worldFlatZone2 - this->worldFlatZone1)/2));
}

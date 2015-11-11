#include "Problems/Rocket/HardSet/TwoEngines/ProblemRocket_HS_TwoEngines.h"


ProblemRocket_HS_TwoEngines::ProblemRocket_HS_TwoEngines(float waveAmplLossPerSec) : Problem(waveAmplLossPerSec), worldWidth(SIZE_DEFAULT_WIDTH), worldHeight(SIZE_DEFAULT_HEIGHT), rocketX(worldWidth/2), rocketY(worldHeight/2), hasLanded(false), hasCrashed(false), hSpeed(0.0), vSpeed(0.0), enginePowerRight(0), enginePowerLeft(0), userControlled(true)
{
	this->setAngle(0);
	this->loadTerrain();
}

void ProblemRocket_HS_TwoEngines::resetRocket(int x, int y)
{
	if (x == -1 || y == -1)
	{
		this->rocketX = this->worldWidth / 2;
		this->rocketY = this->worldHeight/ 2;
	}

	this->setAngle(0);
	this->enginePowerRight = 0;
	this->hSpeed = 0;
	this->vSpeed = 0;
}

//Check if rocket collides with the ground
bool ProblemRocket_HS_TwoEngines::collides(double x, double y)
{
	if (x <= 0 || y <= 0 || x >= this->worldWidth || y >= this->worldHeight)
	{
		cout << "Rocket went missing!" << endl;
		this->hasCrashed = true;
		return true;
	}

	vector<pair<int, int>>::iterator p;

	p = this->getPointBefore(x);

	double terrainY = this->getTerrainPoint(x, *p, *(p + 1));

	if (y <= terrainY)
		return true;
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
bool ProblemRocket_HS_TwoEngines::correctLanding(double hSpeed, double vSpeed, double angle)
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

double ProblemRocket_HS_TwoEngines::getTerrainPoint(double x, pair<int, int> p1, pair<int, int> p2)
{
	int distanceP1P2 = p2.first - p1.first;
	double distanceP1X = x - p1.first;

	double distRatio = distanceP1X / distanceP1P2;

	//cout << "p1 : " << x1 << "," << y1 << endl;
	//cout << "p2 : " << x2 << "," << y2 << endl;
	//cout << "x : " << x << endl;

	return p1.second + (p2.second - p1.second)*distRatio;
}

vector<pair<int, int>>::iterator ProblemRocket_HS_TwoEngines::getPointBefore(double x)
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

void ProblemRocket_HS_TwoEngines::getThrustersForce(double angle, int powerLeft, int powerRight, double& horizontalForce, double & verticalForce)
{
	double vecX = cos(degToRad(angle));
	double vecY = sin(degToRad(angle));

	double hForceLeft = 0;
	double vForceLeft = 0;
	double hForceRight = 0;
	double vForceRight = 0;

	//cout << "Thruster computation : " << vecX << "," << vecY << endl;

	hForceLeft = (powerLeft*THRUSTER_STRENGTH/2*vecX) / 100;
	vForceLeft = (powerLeft*THRUSTER_STRENGTH/2*vecY) / 100;

	hForceRight = (powerRight*THRUSTER_STRENGTH/2*vecX) / 100;
	vForceRight = (powerRight*THRUSTER_STRENGTH/2*vecY) / 100;

	horizontalForce = hForceLeft + hForceRight;
	verticalForce = vForceLeft + vForceRight;

	// Compute the resulting angle change
	//addAngle(0);
	// TODO : If, toi qui aimes les maths : il faut trouver le nouvel angle de la fusée en fonction de la force appliquée par les moteurs. Du coup tu calcules le changement (mettons tu trouve rotation = -5°), et tu appeles la fonction addAngle(rotation)
}

void ProblemRocket_HS_TwoEngines::checkEvents(sf::RenderWindow * window)
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

	if (this->userControlled)
	{
		// Engine control
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			this->addPowerLeft(1);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
			this->addPowerLeft(-1);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
			this->addPowerRight(1);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			this->addPowerRight(-1);
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			this->addPowerRight(-1);
			this->addPowerLeft(-1);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			this->addPowerRight(1);
			this->addPowerLeft(1);
		}
			

		// Angle control
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			this->addAngle(-1);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			this->addAngle(+1);
	}
	
}

void ProblemRocket_HS_TwoEngines::loadTerrain(std::string path)
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
		this->terrain.push_back(pair<int, int>(100, 300));
		this->terrain.push_back(pair<int, int>(200, 0));
		this->terrain.push_back(pair<int, int>(300, 100));
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

void ProblemRocket_HS_TwoEngines::saveTerrain(std::string path)
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

void ProblemRocket_HS_TwoEngines::run(sf::Time elapsedTime)
{
	if (!hasLanded && !hasCrashed)
	{
		//TODO : get that back
		//if (!this->userControlled)
		//{
		//	// Adding agent's influence
		//	this->addAngle(this->desiredRotationChange);
		//	this->addPower(this->desiredPowerChange);
		//	this->desiredPowerChange = 0;
		//	this->desiredRotationChange = 0;
		//}

		// Compute the force applied by the engines
		double hOffset, vOffset;
		getThrustersForce(this->rocketAngle, this->enginePowerLeft, this->enginePowerRight, hOffset, vOffset);

		// Apply that force to the current rocket position
		hSpeed += hOffset * elapsedTime.asSeconds();
		vSpeed += vOffset * elapsedTime.asSeconds() - (MARS_GRAVITY*elapsedTime.asSeconds());

		this->rocketY += vSpeed * elapsedTime.asSeconds();
		this->rocketX += hSpeed * elapsedTime.asSeconds();

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
	{
		
	}
}

// Draw the problem
void ProblemRocket_HS_TwoEngines::draw(sf::RenderWindow * problemWindow, std::vector<sf::Font>* fonts)
{
	this->checkEvents(problemWindow);

	// Drawing terrain
	if (!this->terrain.empty())
	{
		// Iterating on terrain points
		vector<pair<int, int>>::iterator p = this->terrain.begin();
		for (vector<pair<int, int>>::iterator it = this->terrain.begin()+1; it != this->terrain.end(); ++it)
		{
			// For each point, draw a line
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

	// Drawing engine fire right
	if (this->enginePowerRight > 0)
	{
		this->hud_engineFire.setSize(sf::Vector2f(this->enginePowerRight*HUD_SIZE_THRUSTER, 6));
		this->hud_engineFire.setOrigin(this->enginePowerRight*HUD_SIZE_THRUSTER + this->hud_rocketSprite.getLocalBounds().width/2, 3 - 10);
		this->hud_engineFire.setRotation(-this->rocketAngle);
		this->hud_engineFire.setPosition(rocketX*problemWindow->getSize().x / worldWidth,
			problemWindow->getSize().y - (rocketY*problemWindow->getSize().y / worldHeight));

		problemWindow->draw(this->hud_engineFire);
	}

	// Drawing engine fire left
	if (this->enginePowerLeft > 0)
	{
		this->hud_engineFire.setSize(sf::Vector2f(this->enginePowerLeft*HUD_SIZE_THRUSTER, 6));
		this->hud_engineFire.setOrigin(this->enginePowerLeft*HUD_SIZE_THRUSTER + this->hud_rocketSprite.getLocalBounds().width / 2, 3 + 10);
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

	temp = std::to_string(this->enginePowerLeft) + " / " + std::to_string(this->enginePowerRight);
	this->hud_power.setString("Power  : " + temp);

	problemWindow->draw(this->hud_angle);
	problemWindow->draw(this->hud_hSpeed);
	problemWindow->draw(this->hud_vSpeed);
	problemWindow->draw(this->hud_power);
}

void ProblemRocket_HS_TwoEngines::clean()
{
	this->terrain.clear();
}

void ProblemRocket_HS_TwoEngines::init()
{
	// Nothing to do here	
}

void ProblemRocket_HS_TwoEngines::initGraphics(std::vector<sf::Font>* fonts)
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

void ProblemRocket_HS_TwoEngines::setPowerRight(int power)
{
	if (power > 100)
		power = 100;
	else if (power < 0)
		power = 0;
	this->enginePowerRight = power;
}

void ProblemRocket_HS_TwoEngines::setPowerLeft(int power)
{
	if (power > 100)
		power = 100;
	else if (power < 0)
		power = 0;
	this->enginePowerLeft = power;
}

void ProblemRocket_HS_TwoEngines::addPowerRight(int powerOffset)
{
	this->setPowerRight(this->enginePowerRight + powerOffset);
}

void ProblemRocket_HS_TwoEngines::addPowerLeft(int powerOffset)
{
	this->setPowerLeft(this->enginePowerLeft + powerOffset);
}

void ProblemRocket_HS_TwoEngines::setAngle(double angle)
{
	angle += ANGLE_OFFSET;	// Applying offset to have 0° be up
	while (angle >= 360)
		angle -= 360;
	while (angle < 0)
		angle += 360;
		
	this->rocketAngle = angle;
}

void ProblemRocket_HS_TwoEngines::addAngle(double angleOffset)
{
	this->setAngle(this->rocketAngle-ANGLE_OFFSET + angleOffset);
	//cout << "Adding angle" << endl;
}

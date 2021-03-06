#include "Problems/Rocket/ProblemRocket_Terrain.h"

// Returns the terrain point before the given x. If none was found, return end
deque<pair<int, int>>::iterator ProblemRocket_Terrain::getPointBefore(float x)
{
	if (x > this->getWidth())
		return this->terrain.end();

	if (this->terrain.size() < 2)
	{
		cout << "ProblemRocket_Terrain::getPointBefore : ERROR : Terrain is invalid as it contains less than 2 terrain points" << endl;
		return this->terrain.end();
	}

	pair<int, int> p = *this->terrain.begin();
	for (deque<pair<int, int>>::iterator it = this->terrain.begin() + 1; it != this->terrain.end(); ++it)
	{
		if (it->first > x)
			return it - 1;
	}

	cout << "ProblemRocket_Terrain::getPointBefore : ERROR : Didn't find a point before for given x." << endl;
	return this->terrain.end();
}

float ProblemRocket_Terrain::getTerrainPoint(float x, pair<int, int> p1, pair<int, int> p2)
{
	int distanceP1P2 = p2.first - p1.first;
	float distanceP1X = x - p1.first;

	float distRatio = distanceP1X / distanceP1P2;

	return p1.second + (p2.second - p1.second)*distRatio;
}

void ProblemRocket_Terrain::computeLandingZone()
{
	this->terrainFlatZone1 = -1;
	this->terrainFlatZone2 = -1;

	if (this->terrain.size() <= 2)
	{
		this->terrainFlatZone1 = 0;
		this->terrainFlatZone2 = this->getWidth();
	}
	else
	{
		int previousX = this->terrain.front().first;
		int previousY = this->terrain.front().second;
		for (deque<pair<int, int>>::iterator it = this->terrain.begin()+1; it != this->terrain.end(); ++it)
		{
			if (it->second == previousY)
			{
				this->terrainFlatZone1 = previousX;
				this->terrainFlatZone2 = it->first;
				return;
			}
			else
			{
				previousX = it->first;
				previousY = it->second;
			}
		}
	}
}

void ProblemRocket_Terrain::checkTerrainBounds()
{
	for (pair<int, int> p : this->terrain)
	{
		if (p.second > this->getHeight())
			p.second = this->getHeight();
	}

	this->terrain.front().first = 0;
	this->terrain.back().first = this->getWidth();
}

ProblemRocket_Terrain::ProblemRocket_Terrain(int width, int height, int maxTerrainHeight, int minTerrainHeight, float rocketStartX, float rocketStartY, float rocketStartHSpeed, float rocketStartVSpeed, float gravity) : mapWidth(width), mapHeight(height), terrainMaxHeight(maxTerrainHeight), terrainMinHeight(minTerrainHeight), rocketStartX(rocketStartX), rocketStartY(rocketStartY), rocketStartHSpeed(rocketStartHSpeed), rocketStartVSpeed(rocketStartVSpeed), gravity(gravity)
{
	this->generateRandomTerrain();
}

ProblemRocket_Terrain::ProblemRocket_Terrain(int width, int height) : gravity(4)
{
	this->generateRandomTerrain();
}

ProblemRocket_Terrain::ProblemRocket_Terrain(string path) : gravity(4)
{
	this->loadTerrain(path);
}

void ProblemRocket_Terrain::draw(sf::RenderWindow * window)
{
	if (!this->terrain.empty())
	{
		// Iterate on the terrain container, drawin linges between each terrain point
		deque<pair<int, int>>::iterator p = this->terrain.begin();
		for (deque<pair<int, int>>::iterator it = this->terrain.begin() + 1; it != this->terrain.end(); ++it)
		{
			// We resize the terrain in perspective, so that the terrain takes up all the width and height of the screen
			float x1, x2, y1, y2;
			convertCoordinates((float)p->first, (float)p->second, (float)this->getWidth(), (float)this->getHeight(), x1, y1, (float)window->getSize().x, (float)window->getSize().y);
			convertCoordinates((float)it->first, (float)it->second, (float)this->getWidth(), (float)this->getHeight(), x2, y2, (float)window->getSize().x, (float)window->getSize().y);
			
			sf::Vertex line[] =
			{
				sf::Vertex(sf::Vector2f(x1, window->getSize().y - y1)),
				sf::Vertex(sf::Vector2f(x2, window->getSize().y - y2))
			};

			window->draw(line, 2, sf::Lines);

			p = it;
		}
	}
}

void ProblemRocket_Terrain::loadTerrain(std::string name)
{
	this->terrain.clear();
	this->terrainFlatZone1 = -1;
	this->terrainFlatZone2 = -1;
	this->mapWidth = -1;
	this->mapHeight = -1;

	if (name.compare("Default") == 0)
	{
		cout << "ProblemRocket::loadTerrain : Loading default terrain" << endl;
		// Loading default terrain
		this->terrain.push_back(pair<int, int>(0, 600));
		this->terrain.push_back(pair<int, int>(100, 500));
		this->terrain.push_back(pair<int, int>(200, 200));
		/*this->terrain.push_back(pair<int, int>(250, 275));
		this->terrain.push_back(pair<int, int>(265, 275));*/
		this->terrain.push_back(pair<int, int>(300, 100));
		this->terrain.push_back(pair<int, int>(325, 110));
		this->terrain.push_back(pair<int, int>(370, 420));
		this->terrain.push_back(pair<int, int>(380, 430));
		this->terrain.push_back(pair<int, int>(400, 250));
		this->terrain.push_back(pair<int, int>(500, 100));
		this->terrain.push_back(pair<int, int>(800, 100));
		this->terrain.push_back(pair<int, int>(1000, 200));

		// Terrain data
		this->mapWidth = 1000;
		this->mapHeight = 1000;
		this->terrainFlatZone1 = 500;
		this->terrainFlatZone2 = 800;
		this->windHorizontal = 0;
		this->windVertical = 0;

		// Rocket start
		this->rocketStartX = 200;
		this->rocketStartY = 800;
		this->rocketStartHSpeed = 0;
		this->rocketStartVSpeed = 0;
		this->rocketAngle = 90;
		this->rocketStartPower = 0;
	}
	else if (name.compare("Base") == 0)
	{
		cout << "ProblemRocket::loadTerrain : Loading default terrain" << endl;
		// Loading default terrain
		this->terrain.push_back(pair<int, int>(0, 100));
		this->terrain.push_back(pair<int, int>(1000, 100));


		// Terrain data
		this->mapWidth = 1000;
		this->mapHeight = 1000;
		this->terrainFlatZone1 = 0;
		this->terrainFlatZone2 = 1000;
		this->windHorizontal = 0;
		this->windVertical = 0;

		// Rocket start
		this->rocketStartX = 500;
		this->rocketStartY = 500;
		this->rocketStartHSpeed = 0;
		this->rocketStartVSpeed = 0;
		this->rocketAngle = 90;
		this->rocketStartPower = 50;
	}
	else
	{
		string filePath = PATH_RES_TERRAINS;
		filePath += name;
		filePath += ".lvl";

		// XML document creation
		pugi::xml_document doc;

		// Load document
		pugi::xml_parse_result result = doc.load_file(filePath.data());
		if (result.status != pugi::xml_parse_status::status_ok)
		{
			// An error occured
			std::cout << "ERROR : ProblemRocket::loadTerrain : unable to parse given file : " << filePath << std::endl;
			this->loadTerrain("Default");
			return;
		}

		cout << "Loading terrain " << filePath << endl;

		// Loading terrain data
		pugi::xml_node terrainNode = doc.child("terrain");
		this->mapWidth = terrainNode.attribute("width").as_int();
		this->mapHeight = terrainNode.attribute("height").as_int();
		this->terrainFlatZone1 = terrainNode.attribute("flat1").as_int();
		this->terrainFlatZone2 = terrainNode.attribute("flat2").as_int();
		this->windHorizontal = terrainNode.attribute("windH").as_float();
		this->windVertical = terrainNode.attribute("windV").as_float();

		// Loading rocket data
		this->rocketStartX = terrainNode.attribute("rocketX").as_float();
		this->rocketStartY = terrainNode.attribute("rocketY").as_float();
		this->rocketStartHSpeed = terrainNode.attribute("rocketH").as_float();
		this->rocketStartVSpeed = terrainNode.attribute("rocketV").as_float();
		this->rocketAngle = terrainNode.attribute("rocketA").as_float();
		this->rocketStartPower = terrainNode.attribute("rocketStartP").as_float();

		// Loading terrain points
		pugi::xml_node point = terrainNode.first_child();
		// iterate over genome nodes in the genomes node
		while (point != NULL)
		{
			pair<int, int> p;
			p.first = point.attribute("x").as_int();
			p.second = point.attribute("y").as_int();

			this->terrain.push_back(p);

			point = point.next_sibling();
		}
	}
}

void ProblemRocket_Terrain::saveTerrain(std::string name)
{
	this->computeLandingZone();

	if (this->terrainFlatZone1 < 0)
	{
		cout << "ERROR : the terrain doesn't have a flatzone" << endl;
		return;
	}
	else if (name.compare("Default") == 0)
	{
		cout << "ProblemRocket::saveTerrain : ERROR save path can't be 'Default'. Aborting save" << endl;
		return;
	}
	else if (name.compare("Base") == 0)
	{
		cout << "ProblemRocket::saveTerrain : ERROR save path can't be 'Base'. Aborting save" << endl;
		return;
	}
	else
	{
		cout << "ProblemRocket::saveTerrain : saving terrain " << name << "..." << endl;

		// Creating the xml doc
		pugi::xml_document doc;

		// Set XML declaration
		auto declarationNode = doc.append_child(pugi::node_declaration);
		declarationNode.append_attribute("version") = "1.0";
		declarationNode.append_attribute("encoding") = "UTF-8";
		declarationNode.append_attribute("standalone") = "yes";

		// Set XML root node
		pugi::xml_node terrainNode = doc.append_child("terrain");

		// Saving world data
		terrainNode.append_attribute("width").set_value(this->mapWidth);
		terrainNode.append_attribute("height").set_value(this->mapHeight);
		terrainNode.append_attribute("flat1").set_value(this->terrainFlatZone1);
		terrainNode.append_attribute("flat2").set_value(this->terrainFlatZone2);
		terrainNode.append_attribute("maxHeight").set_value(this->terrainMaxHeight);
		terrainNode.append_attribute("minHeight").set_value(this->terrainMinHeight);
		terrainNode.append_attribute("windH").set_value(this->windHorizontal);
		terrainNode.append_attribute("windV").set_value(this->windVertical);

		// Saving rocket start data
		terrainNode.append_attribute("rocketX").set_value(this->rocketStartX);
		terrainNode.append_attribute("rocketY").set_value(this->rocketStartY);
		terrainNode.append_attribute("rocketH").set_value(this->rocketStartHSpeed);
		terrainNode.append_attribute("rocketV").set_value(this->rocketStartVSpeed);
		terrainNode.append_attribute("rocketA").set_value(this->rocketAngle);
		terrainNode.append_attribute("rocketStartP").set_value(this->rocketStartPower);

		// terrain points
		for (deque<pair<int, int>>::iterator it = this->terrain.begin(); it != this->terrain.end(); ++it)
		{
			pugi::xml_node pointNode = terrainNode.append_child("point");

			// Saving genome data
			pointNode.append_attribute("x").set_value(it->first);
			pointNode.append_attribute("y").set_value(it->second);
		}

		string filePath = PATH_RES;
		filePath += PATH_RES_TERRAINS;
		filePath += name;
		filePath += ".lvl";
		std::cout << "Save result : " << filePath.data() << " : " << doc.save_file(filePath.data()) << std::endl;
	}
}

// Leave -1, -1 to keep the current size
void ProblemRocket_Terrain::generateRandomTerrain(int width, int height)
{
	//TODO : generate random terrain, with one flat zone, and points between terrainMinHeight and terrainMaxHeight
}

deque<pair<int, int>>::iterator ProblemRocket_Terrain::getClosestPointFrom(float x, float y, bool& found, float threshold)
{
	for (deque<pair<int, int>>::iterator it = this->terrain.begin(); it != this->terrain.end(); ++it)
	{
		if (abs(it->first - x) <= threshold)
		{
			if (sqrt((x - it->first)*(x - it->first) +
				(y - it->second)*(y - it->second)))
			{
				found = true;
				return it;
			}
		}
	}
	found = false;
	return this->terrain.end();
}

// Reorders the points so that the deque is sorted by the x components of points
void ProblemRocket_Terrain::reorderPoints()
{
	bool success = false;
	while (!success)
	{
		bool attempt = true;
		for (deque<pair<int, int>>::iterator it = this->terrain.begin(); it != this->terrain.end(); ++it)
		{
			if ((it + 1) != this->terrain.end() && it->first > (it+1)->first)
			{
				// Invert the 2 members
				float x, y;
				x = (float)it->first;
				y = (float)it->second;

				it->first = (it + 1)->first;
				it->second = (it + 1)->second;

				(it + 1)->first = (int)x;
				(it + 1)->second = (int)y;
				attempt = false;
			}
		}

		if (attempt)
			success = true;
	}
}

void ProblemRocket_Terrain::addPoint(float x, float y)
{
	if (x < 0 || x >= this->getWidth() || y < 0 || y >= this->getHeight())
		return;

	pair<int, int> p = pair<int, int>(static_cast<int>(round(x)), static_cast<int>(round(y)));
	if (this->terrain.empty() || this->terrain.begin()->first > x)
		this->terrain.push_front(p);
	else if ((this->terrain.end()-1)->first < x)
		this->terrain.push_back(p);
	else
	{
		for (deque<pair<int, int>>::iterator it = this->terrain.begin(); it != this->terrain.end(); ++it)
		{
			if (it->first < x)
			{
				this->terrain.insert(it, p);
				return;
			}
		}
	}
	return;
}

void ProblemRocket_Terrain::addFlat(float x)
{
	if (x < 0 || x >= this->getWidth())
		return;

	pair<int, int> p = pair<int, int>(static_cast<int>(round(x)), 0);

	if (this->terrain.empty() || this->terrain.front().first > x)
	{
		p.second = 100;
		this->terrain.push_front(p);
	}
	else if ((this->terrain.end() - 1)->first < x)
	{
		p.second = (this->terrain.end() - 1)->second;
		this->terrain.push_back(p);
	}
	else
	{
		for (deque<pair<int, int>>::iterator it = this->terrain.begin(); it != this->terrain.end(); ++it)
		{
			if (it->first > x)
			{
				p.second = (it-1)->second;
				this->terrain.insert(it-1, p);
				return;
			}
		}
	}
	return;
}

void ProblemRocket_Terrain::removePoint(deque<pair<int, int>>::iterator it)
{
	this->terrain.erase(it);
}

void ProblemRocket_Terrain::getWorldCoordinates(float screenX, float screenY, sf::RenderWindow * window, float & worldX, float & worldY)
{
	convertCoordinates((float)screenX, (float)window->getSize().y - screenY, (float)window->getSize().x, (float)window->getSize().y, worldX, worldY, (float)this->mapWidth, (float)this->mapHeight);
}

void ProblemRocket_Terrain::getScreenCoordinates(float worldX, float worldY, float screenWidth, float screenHeight, float & screenX, float & screenY)
{
	convertCoordinates(worldX, worldY, (float)this->mapWidth, (float)this->mapHeight, screenX, screenY, screenWidth, screenHeight);
}

// Checks if the given position is colliding with terrain
bool ProblemRocket_Terrain::isOnMap(float x, float y)
{
	if (x <= 0 || y <= 0 || x >= this->mapWidth || y >= this->mapHeight)
		return false;
	else
		return true;
}

bool ProblemRocket_Terrain::collides(float x, float y, float hitboxHalfSize)
{
	if (!this->isOnMap(x, y))
		return false;
		

	// Getting the terrain's y at coordinate x
	deque<pair<int, int>>::iterator p;
	p = this->getPointBefore(x);
	if (p == this->terrain.end())
		return false;
	float terrainY = this->getTerrainPoint(x, *p, *(p + 1));

	// Checking collision
	if (y - hitboxHalfSize <= terrainY)
		return true;
	else
		return false;
}

float ProblemRocket_Terrain::getTerrainPoint(float x)
{
	deque<pair<int, int>>::iterator p;
	p = this->getPointBefore(x);

	if (p != this->terrain.end())
		return this->getTerrainPoint(x, *p, *(p + 1));
	else
		return -1;
}

float ProblemRocket_Terrain::getGravity()
{
	return this->gravity;
}

void ProblemRocket_Terrain::getHighestPointBeforeLandingZone(float x, float y, float & highestPointX, float & highestPointY)
{
	highestPointX = -1.0f;
	highestPointY = -1.0f;

	// 3 possibilities : we're left of the lz, or we're right of the lz, or we're in the lz

	// We're in the lz, return
	if (x >= this->terrainFlatZone1 && x <= this->terrainFlatZone2)
		return;
	// We're left of the lz
	else if (x < this->terrainFlatZone1)
	{
		float peak = 0.0f;
		for (deque<pair<int, int>>::iterator p = this->getPointBefore(x); p != this->terrain.end(); ++p)
		{
			if (p->first > this->terrainFlatZone1)
				return;
			else if (highestPointY < p->second)
			{
				highestPointX = (float)p->first;
				highestPointY = (float)p->second;
			}
		}
	}
	// We're right of the lz
	else
	{
		float peak = 0.0f;
		for (deque<pair<int, int>>::iterator p = this->getPointBefore(x)+1; p != this->terrain.begin(); --p)
		{
			if (p == this->terrain.end())
				continue;

			if (p->first < this->terrainFlatZone2)
				return;
			else if (highestPointY < p->second)
			{
				highestPointX = (float)p->first;
				highestPointY = (float)p->second;
			}
		}
	}
}

void ProblemRocket_Terrain::getClosestPointFromRocket(float rocketX, float rocketY, float & pointX, float & pointY, float & distance)
{
	//TODO if : la fonction. Du coup la fus�e est en rocketX/rocketY. Tu me retourne : 
	/* - pointX : le x du point
	 * - pointY : le y du point
	 * - distance : la distance entre les points (rocketX,rocketY) et (pointX, pointY)
	*/
	vector <pair<pair<int,int>,pair<int,int>>> segments;

	for (deque <pair<int, int>>::iterator it = this->terrain.begin(); it != terrain.end(); ++it)
	{
		if (it + 1 != terrain.end()) {
			segments.push_back(pair<pair<int, int>, pair<int, int>>(pair<int, int>(it->first, it->second), pair<int, int>((it + 1)->first, (it + 1)->second)));
		}

	}
	float d = 100000000;
	float tempD;

	pair<float, float> Point;
	pair<float, float> tempP;
	for (pair<pair<int, int>, pair<int, int>> s : segments) {
		tempP = this->projection(s.first, s.second, pair<float, float>(rocketX, rocketY));
		if (tempP.first < s.first.first)
			tempP = s.first;
		if (tempP.first > s.second.first)
			tempP = s.second;
		tempD = sqrt((tempP.first - rocketX)*(tempP.first - rocketX) + (tempP.second - rocketY)*(tempP.second - rocketY));
		if (tempD < d) {
			d = tempD;
			Point = tempP;
		}

	}
	pointX = Point.first;
	pointY = Point.second;
	distance = d;
}

void ProblemRocket_Terrain::setRocketStart(float rocketX, float rocketY)
{
	this->rocketStartX = rocketX;
	this->rocketStartY = rocketY;
}

void ProblemRocket_Terrain::setRocketStartSpeed(float hSpeed, float vSpeed)
{
	this->rocketStartHSpeed = hSpeed;
	this->rocketStartVSpeed = vSpeed;
}

void ProblemRocket_Terrain::setWind(float hWind, float vWind)
{
	this->windHorizontal = hWind;
	this->windVertical = vWind;
}

void ProblemRocket_Terrain::setTerrainWidth(int width)
{
	if (width < 500)
		width = 500;
	else if (width > 10000)
		width = 10000;

	this->mapWidth = width;

	this->checkTerrainBounds();
}

void ProblemRocket_Terrain::setTerrainHeigh(int height)
{
	if (height < 500)
		height = 500;
	else if (height > 10000)
		height = 10000;

	this->mapHeight = height;

	this->checkTerrainBounds();
}

void ProblemRocket_Terrain::setRocketStartPower(float startPower)
{
	if (startPower > 100)
		startPower = 100;
	else if (startPower < 0)
		startPower = 0;

	this->rocketStartPower = startPower;
}

float ProblemRocket_Terrain::getRocketStartPower()
{
	return this->rocketStartPower;
}

deque<pair<int, int>>* ProblemRocket_Terrain::getTerrain()
{
	return &this->terrain;
}

void ProblemRocket_Terrain::getLandingZone(float & landing1, float & landing2)
{
	landing1 = (float)this->terrainFlatZone1;
	landing2 = (float)this->terrainFlatZone2;
}

void ProblemRocket_Terrain::getTerrainDimensions(float & terrainWidth, float & terrainHeight)
{
	terrainWidth = (float)this->getWidth();
	terrainHeight = (float)this->getHeight();
}

int ProblemRocket_Terrain::getWidth()
{
	return this->mapWidth;
}

int ProblemRocket_Terrain::getHeight()
{
	return this->mapHeight;
}

void ProblemRocket_Terrain::getRocketStart(float & rocketX, float & rocketY, float & rocketHorizontalSpeed, float & rocketVerticalSpeed, float& rocketAngle, float& rocketStartPower)
{
	this->getRocketStartCoordinates(rocketX, rocketY);
	rocketHorizontalSpeed = this->rocketStartHSpeed;
	rocketVerticalSpeed = this->rocketStartVSpeed;
	rocketAngle = this->rocketAngle;
	rocketStartPower = this->rocketStartPower;
}

void ProblemRocket_Terrain::getRocketStartCoordinates(float & x, float & y)
{
	x = this->rocketStartX;
	y = this->rocketStartY;
}

void ProblemRocket_Terrain::getWind(float & windHorizontal, float & windVertical)
{
	windHorizontal = this->windHorizontal;
	windVertical = this->windVertical;
}

pair<float, float> ProblemRocket_Terrain::projection(pair<int, int> A, pair<int, int> B, pair<float, float> P) {

	float xA = A.first;
	float yA = A.second;
	float xB = B.first;
	float yB = B.second;

	float a = (yB - yA) / (xB - xA);
	float b = yA - a * xA;
	pair<float,float> p;

	p.first = (P.first - a*b + a * P.second) / (1.0f + a * a);
	p.second = b + a * (P.first - a*b + a * P.second) / (1.0f + a * a);
	
	return p;
}
#include "Problems/Rocket/RocketTerrainEditor.h"


RocketTerrainEditor::RocketTerrainEditor(float waveAmplLossPerSec) : Problem(waveAmplLossPerSec), currentLevelName("Default"), isPointSelected(false)
{
}

void RocketTerrainEditor::checkEvents(sf::RenderWindow * window)
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		this->handleEvent(window, event);
	}
}

bool RocketTerrainEditor::handleEvent(sf::RenderWindow * window, sf::Event event)
{
	if (Problem::handleEvent(window, event))
		return true;
	else
	{
		float xWorld, yWorld;
		int rocketX, rocketY;
		string temp;
		switch (event.type)
		{
		case sf::Event::KeyPressed :
			switch (event.key.code)
			{
			// Delete : remove point if selected
			case sf::Keyboard::Delete :
				if (this->isPointSelected)
				{
					this->terrain.removePoint(this->selectedPoint);
					this->isPointSelected = false;
				}
					
				return true;

			// B : Load basic terrain
			case sf::Keyboard::B:
				this->terrain.loadTerrain("Base");
				this->currentLevelName = "Base";
				return true;

			// D : Load default terrain
			case sf::Keyboard::D:
				this->terrain.loadTerrain("Default");
				this->currentLevelName = "Default";
				return true;

			// L : Load terrain
			case sf::Keyboard::L:
				cout << "Enter terrain to load : ";
				cin >> temp;
				this->loadTerrain(temp);
				this->currentLevelName = temp;
				return true;

			// R : Set rocket position
			case sf::Keyboard::R:
				cout << "Enter rocket x : ";
				cin >> rocketX;
				cout << "Enter rocket y : ";
				cin >> rocketY;
				this->terrain.setRocketStart(rocketX, rocketY);
				this->rename();
				return true;

			// W : Set wind
			case sf::Keyboard::W:
				cout << "Enter wind hForce : ";
				cin >> xWorld;
				cout << "Enter wind vForce : ";
				cin >> yWorld;
				this->terrain.setWind(xWorld, yWorld);
				this->rename();
				return true;

				// V : Set velocity
			case sf::Keyboard::V:
				cout << "Enter rocket hVelocity : ";
				cin >> xWorld;
				cout << "Enter rocket vVelocity : ";
				cin >> yWorld;
				this->terrain.setRocketStartSpeed(xWorld, yWorld);
				this->rename();
				return true;

			// S : Save terrain
			case sf::Keyboard::S:
				cout << "Name your terrain : ";
				cin >> temp;
				this->saveTerrain(temp);
				this->currentLevelName = temp;
				return true;
			}
			break;
		case sf::Event::MouseButtonPressed :
			switch (event.mouseButton.button)
			{
			// Left mouse button : select point
			case sf::Mouse::Left:
				this->terrain.getWorldCoordinates(event.mouseButton.x, event.mouseButton.y, window, xWorld, yWorld);

				this->selectedPoint = this->terrain.getClosestPointFrom(xWorld, yWorld, this->isPointSelected);
				return true;

			// Right mouse button : insert a point
			case sf::Mouse::Right:
				// If shift is pressed : add flat
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
				{
					this->terrain.getWorldCoordinates(event.mouseButton.x, event.mouseButton.y, window, xWorld, yWorld);
					this->terrain.addFlat(xWorld );
					this->terrain.reorderPoints();
				}
				// Else, add normal point
				else
				{
					this->terrain.getWorldCoordinates(event.mouseButton.x, event.mouseButton.y, window, xWorld, yWorld);
					this->terrain.addPoint(xWorld, yWorld);
					this->terrain.reorderPoints();
				}
				this->rename();

				return true;
			}
			break;
		case sf::Event::MouseMoved:
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->isPointSelected)
			{
				// Drag and drop the thing
				this->terrain.getWorldCoordinates(event.mouseMove.x, event.mouseMove.y, window, xWorld, yWorld);

				this->selectedPoint->first = xWorld;
				this->selectedPoint->second = yWorld;

				this->terrain.reorderPoints();
				this->rename();

				return true;
			}
			break;
		}
	}

	return false;
}

void RocketTerrainEditor::loadTerrain(string path)
{
	this->terrain.loadTerrain(path);
}

void RocketTerrainEditor::saveTerrain(string path)
{
	this->terrain.saveTerrain(path);
}

void RocketTerrainEditor::generateTerrain(int width, int height)
{
	this->terrain.generateRandomTerrain(width, height);
}

void RocketTerrainEditor::rename()
{
	if (this->currentLevelName.compare("Default") == 0 || this->currentLevelName.compare("Base") == 0)
		this->currentLevelName = "Untitled";
}

void RocketTerrainEditor::run(sf::Time elapsedTime)
{
}

// Draw the problem
void RocketTerrainEditor::draw(sf::RenderWindow * window)
{
	this->checkEvents(window);

	this->terrain.draw(window);

	// Drawing text
	string temp;

	// Title
	this->hud_text.setCharacterSize(30);
	this->hud_text.setString("Rocket Terrain Editor");
	this->hud_text.setPosition(window->getSize().x / 2 - this->hud_text.getLocalBounds().width / 2, 5);
	window->draw(this->hud_text);

	// Terrain data
	this->hud_text.setCharacterSize(20);
	this->hud_text.setString("Curently editing : " + this->currentLevelName);
	this->hud_text.setPosition(10, 5);
	window->draw(this->hud_text);

	// Starting rocket values
	float startH, startV, startX, startY, windH, windV;
	this->terrain.getRocketStart(startX, startY, startH, startV);
	this->terrain.getWind(windH, windV);

	this->hud_text.setString("Starting x : " + std::to_string(startX));
	this->hud_text.setPosition(10, 25);
	window->draw(this->hud_text);

	this->hud_text.setString("Starting y : " + std::to_string(startY));
	this->hud_text.setPosition(10, 45);
	window->draw(this->hud_text);

	this->hud_text.setString("Starting hSpeed : " + std::to_string(startH));
	this->hud_text.setPosition(10, 65);
	window->draw(this->hud_text);

	this->hud_text.setString("Starting vSpeed : " + std::to_string(startV));
	this->hud_text.setPosition(10, 85);
	window->draw(this->hud_text);

	this->hud_text.setString("Starting hWind : " + std::to_string(windH));
	this->hud_text.setPosition(10, 105);
	window->draw(this->hud_text);

	this->hud_text.setString("Starting vWind : " + std::to_string(windV));
	this->hud_text.setPosition(10, 125);
	window->draw(this->hud_text);
}

void RocketTerrainEditor::clean()
{
}

void RocketTerrainEditor::init()
{
	this->loadTerrain("Default");
}

void RocketTerrainEditor::initGraphics(std::vector<sf::Font>* fonts)
{
	// Text
	this->hud_text.setFont(fonts->at(0));
	this->hud_text.setCharacterSize(20);
	this->hud_text.setColor(sf::Color::White);

	// Rocket circle
	this->rocketCircle.setOrigin(3, 3);
	this->rocketCircle.setFillColor(sf::Color::Blue);
	this->rocketCircle.setRadius(3);
	this->rocketCircle.setPosition(100, 100);
}
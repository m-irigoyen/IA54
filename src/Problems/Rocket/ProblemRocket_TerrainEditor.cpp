#include "Problems/Rocket/ProblemRocket_TerrainEditor.h"


ProblemRocket_TerrainEditor::ProblemRocket_TerrainEditor(float waveAmplLossPerSec) : Problem(waveAmplLossPerSec), currentLevelName("Default"), isPointSelected(false)
{
}

void ProblemRocket_TerrainEditor::checkEvents(sf::RenderWindow * window)
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		this->handleEvent(window, event);
	}
}

bool ProblemRocket_TerrainEditor::handleEvent(sf::RenderWindow * window, sf::Event event)
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

				// P : Set wind
			case sf::Keyboard::F:
				cout << "Enter rocket start power : ";
				cin >> xWorld;
				this->terrain.setRocketStartPower(xWorld);
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

			case sf::Keyboard::Add :
				this->terrain.setTerrainWidth(this->terrain.getWidth() + 10);
				this->terrain.setTerrainHeigh(this->terrain.getHeight() + 10);
				return true;

			case sf::Keyboard::Subtract:
				this->terrain.setTerrainWidth(this->terrain.getWidth() - 10);
				this->terrain.setTerrainHeigh(this->terrain.getHeight() - 10);
				return true;

				//Rocket one shortcuts
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
			// Left mouse button : select point
			case sf::Mouse::Left:
				// If ctrl is pressed, set start position
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)
					|| sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
				{
					this->terrain.getWorldCoordinates(event.mouseButton.x, event.mouseButton.y, window, xWorld, yWorld);
					this->terrain.setRocketStart(xWorld, yWorld);
				}
				else
				{
					// else
					this->terrain.getWorldCoordinates(event.mouseButton.x, event.mouseButton.y, window, xWorld, yWorld);

					this->selectedPoint = this->terrain.getClosestPointFrom(xWorld, yWorld, this->isPointSelected);
				}
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
				if (this->selectedPoint != this->terrain.getTerrain()->end())
				{
					// Drag and drop the thing
					this->terrain.getWorldCoordinates(event.mouseMove.x, event.mouseMove.y, window, xWorld, yWorld);

					this->selectedPoint->first = xWorld;
					this->selectedPoint->second = yWorld;

					this->terrain.reorderPoints();
					this->rename();
					this->terrain.checkTerrainBounds();
				}

				return true;
			}
			break;
		}
	}

	return false;
}

void ProblemRocket_TerrainEditor::loadTerrain(string path)
{
	this->terrain.loadTerrain(path);
}

void ProblemRocket_TerrainEditor::saveTerrain(string path)
{
	this->terrain.saveTerrain(path);
}

void ProblemRocket_TerrainEditor::generateTerrain(int width, int height)
{
	this->terrain.generateRandomTerrain(width, height);
}

void ProblemRocket_TerrainEditor::rename()
{
	if (this->currentLevelName.compare("Default") == 0 || this->currentLevelName.compare("Base") == 0)
		this->currentLevelName = "Untitled";
}

void ProblemRocket_TerrainEditor::run(sf::Time elapsedTime)
{
}

// Draw the problem
void ProblemRocket_TerrainEditor::draw(sf::RenderWindow * window)
{
	this->checkEvents(window);

	this->terrain.draw(window);

	// Drawing start position
	sf::CircleShape circle;
	circle.setRadius(4);
	circle.setFillColor(sf::Color::Green);
	circle.setOrigin(4, 4);

	float x, y, dontCare;
	this->terrain.getRocketStart(x, y, dontCare, dontCare, dontCare, dontCare);

	convertCoordinates(x, y, this->terrain.getWidth(), this->terrain.getHeight(), x, y, window->getSize().x, window->getSize().y);
	circle.setPosition(x, window->getSize().y - y);
	window->draw(circle);

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
	float startH, startV, startX, startY, windH, windV, rocketAngle, rocketStartPower;
	this->terrain.getRocketStart(startX, startY, startH, startV, rocketAngle, rocketStartPower);
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

	this->hud_text.setString("Starting angle : " + std::to_string(rocketAngle));
	this->hud_text.setPosition(10, 145);
	window->draw(this->hud_text);

	this->hud_text.setString("Starting power : " + std::to_string(rocketStartPower));
	this->hud_text.setPosition(10, 165);
	window->draw(this->hud_text);
}

void ProblemRocket_TerrainEditor::clean()
{
}

void ProblemRocket_TerrainEditor::init()
{
	this->loadTerrain("Default");
}

void ProblemRocket_TerrainEditor::initGraphics(std::vector<sf::Font>* fonts)
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
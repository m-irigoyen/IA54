#include "Problems/Rocket/RocketTerrainEditor.h"


RocketTerrainEditor::RocketTerrainEditor(float waveAmplLossPerSec) : Problem(waveAmplLossPerSec), currentLevelName("Default")
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
		return false;
}

void RocketTerrainEditor::loadTerrain(string path)
{
	this->terrain.loadTerrain(path);
}

void RocketTerrainEditor::saveTerrain(string path)
{
}

void RocketTerrainEditor::generateTerrain(int width, int height)
{
	this->terrain.generateRandomTerrain(width, height);
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
	float startH, startV, startX, startY;
	this->terrain.getRocketStart(startX, startY, startH, startV);

	this->hud_text.setString("Starting hSpeed : " + std::to_string(startH));
	this->hud_text.setPosition(10, 5);
	window->draw(this->hud_text);

	this->hud_text.setString("Starting vSpeed : " + std::to_string(startV));
	this->hud_text.setPosition(10, 25);
	window->draw(this->hud_text);

	this->hud_text.setString("Starting x : " + std::to_string(startX));
	this->hud_text.setPosition(10, 45);
	window->draw(this->hud_text);

	this->hud_text.setString("Starting y : " + std::to_string(startY));
	this->hud_text.setPosition(10, 65);
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
}
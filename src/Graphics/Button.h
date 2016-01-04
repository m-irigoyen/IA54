#ifndef GRAPHICVIEW_H_
#define GRAPHICVIEW_H_

#include <string>
#include "SFML/Graphics.hpp"

using namespace std;

class Button
{
public:
	Button(sf::Sprite* buttonOn, sf::Sprite* buttonOff, sf::Text* text);

	void draw(sf::RenderWindow* window, float x, float y);
	void setTarget(bool* target);
	void setString(string text);

private:
	sf::Sprite* buttonOn;
	sf::Sprite* buttonOff;

	string theString;
	sf::Text* text;

	bool* targetValue;
};

#endif
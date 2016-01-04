#ifndef BUTTON_H_
#define BUTTON_H_

/**
*	The Nework class handles TCP communication with unity. It can send and receive messages.
*	Messages begin with "BEG " an end with " END". How the messages are sent is not the user's concern.
*
*	We use TCP : so we're sure every message will be recieved.
*/

#include <string>
#include <iostream>
#include "SFML/Graphics.hpp"

using namespace std;

class Button
{
public:
	Button(string text, sf::Sprite* buttonOn, sf::Sprite* buttonOff, sf::Text* displayText);

	void setTarget(bool* target);
	void draw(sf::RenderWindow* window);

	bool isInitialised();

private:
	bool* state;
	string text;
	sf::Text* displayText;
	sf::Sprite* buttonOn;
	sf::Sprite* buttonOff;
};

#endif


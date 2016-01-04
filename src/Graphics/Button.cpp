#include "Button.h"

Button::Button(sf::Sprite * buttonOn, sf::Sprite * buttonOff, sf::Text * text)
{
	if (buttonOn != NULL)
		this->buttonOn = buttonOn;
	if (buttonOff != NULL)
		this->buttonOff = buttonOff;
	if (text != NULL)
		this->text = text;
}

void Button::draw(sf::RenderWindow * window, float x, float y)
{
	if (*targetValue)
	{
		this->buttonOn->setPosition(x - this->buttonOn->getGlobalBounds().width / 2,
			y - this->buttonOn->getGlobalBounds().height / 2);
		this->text->setString(this->theString + " : on");
		this->text->setPosition(x - this->text->getGlobalBounds().width / 2,
			y - this->text->getGlobalBounds().height / 2);

		window->draw(*this->buttonOn);
		window->draw(*this->text);
	}
	else
	{

	}
}

void Button::setTarget(bool * target)
{
	if (target != NULL)
		this->targetValue = target;
}

void Button::setString(string text)
{
	this->theString = text;
}

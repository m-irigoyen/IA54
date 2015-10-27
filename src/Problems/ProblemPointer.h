#ifndef PROBLEMPOINTER_H_
#define PROBLEMPOINTER_H_

#include <iostream>
#include "Problem.h"
#include <SFML/Graphics.hpp>

#define FREQUENCY_OFFSET 10
#define FREQUENCY_RANGE 1
#define AMPLITUDE_OFFSET 1
#define AMPLITUDE_RANGE 1

/*
* The Problem class creates and run the problem to be solved. (pendulum, drone, etc)
*/

class ProblemPointer : public Problem
{
protected:
	sf::CircleShape& secondPointer;

	int windowWidth;
	int windowHeight;

	float currentMouseX;
	float currentMouseY;

	float frequencyOffset;
public:
	ProblemPointer(int width, int height, sf::CircleShape& secondPointer);

	virtual void run(sf::Time elapsedTime);

	void setSecondPointerPosition(float x, float y);
	void getMousePointerPosition(float& x, float& y);
	void getSecondPointerPosition(float& x, float& y);
	void setCurrentMouse(float x, float y);

	void getWindowDimensions(int& width, int& height);

	float getFrequencyOffset();
	void incrementFrequencyOffset();
	void decrementFrequencyOffset();
};

#endif


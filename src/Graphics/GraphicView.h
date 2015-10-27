#ifndef GRAPHICVIEW_H_
#define GRAPHICVIEW_H_

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "World/World.h"
// The problems
#include "Problems/ProblemPointer.h"
#include "Problems/ProblemDrones.h"
#include "Problems/ProblemRocket.h"

#define RECEPTOR_RADIUSSIZE 6
#define EMITTER_RADIUSSIZE 6
#define WAVE_SIZE 2

/*
*   The GraphicView handles the GUI, drawing and displaying, etc.
*/

class GraphicView
{
private:
	sf::RenderWindow* window;			// The window
	sf::RenderWindow* problemWindow;	// The problem's window
	World* world;						// Pointer to the world
	Problem* problem;					// Pointer to the problem

	// The shapes for all the objects
	// TODO : (optimise) keep only one and set its position for every object before drawing
	std::vector<sf::CircleShape> receptors;
	std::vector<sf::CircleShape> emitters;
	std::vector<sf::CircleShape> waves;

	// display flags : if its off dont display the corresponding objects
	bool displaySimulator;
	bool displayProblem;

	bool displayWaves;
	bool displayReceptors;
	bool displayEmitters;

	// Used to compute the alpha component of waves
	float maxAmplitude;

	PROBLEM_TYPE problemType;

	void toggle(bool& toToggle);

public:
	GraphicView();

	void Init(int height, int width, Problem* problem);		// Init the window
	void Draw();							// Draw stuff

	// Setters
	void setDisplayWaves(bool displayWaves);
	void setDisplayEmitters(bool displayEmitters);
	void setDisplayReceptors(bool displayReceptors);
	void setMaxAmplitude(float amplitude);
	sf::RenderWindow* getWindow();
	void SetWorld(World* world);
	void setProblem(Problem* problem);
	void setProblemType(PROBLEM_TYPE type);

	// Toggle displaying the waves
	void toggleDisplayWaves();
	void toggleDisplayReceptors();
	void toggleDisplayEmitters();
	void toggleDisplaySimulator();
	void toggleDisplayProblem();

	~GraphicView(void);
};

#endif

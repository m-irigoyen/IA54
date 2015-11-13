#ifndef GRAPHICVIEW_H_
#define GRAPHICVIEW_H_

#include <iostream>
#include <deque>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "World/World.h"
// The problems
#include "Problems/Pointer/ProblemPointer.h"
#include "Problems/Drones/ProblemDrones.h"
//#include "Problems/Rocket/OneEngine/ProblemROCKET_ONEEngine.h"

#define RECEPTOR_RADIUSSIZE 6
#define EMITTER_RADIUSSIZE 6
#define WAVE_SIZE 2

#define WAVE_AMPLITUDE_MAX 100	// Threshold used for making wave transparent with attenuation

using namespace std;

/*
*   The GraphicView handles the GUI, drawing and displaying, etc.
*/
class GraphicView
{
private:
	sf::RenderWindow* window;			// The window
	sf::RenderWindow* problemWindow;	// The problem's window
	//TODO: intercept close events from the problem window

	World* world;						// Pointer to the world
	Problem* problem;					// Pointer to the problem

	// display flags : if its off dont display the corresponding objects
	bool displaySimulator;
	bool displayProblem;

	bool displayWaves;
	bool displayWaveOpacity;
	bool displayReceptors;
	bool displayEmitters;

	// Used to compute the alpha component of waves
	float maxAmplitude;

	PROBLEM_TYPE problemType;

	void toggle(bool& toToggle);

	vector<sf::Font> fonts;

	//GUI
	sf::Text text;
	sf::Text placingAgentText;	// Data given by the simulator

public:
	GraphicView();

	void Init(int width, int height, Problem* problem);		// Init the window
	void Draw();							// Draw stuff
	void clean();	// Cleans the graphics stuff

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

	// GUI
	void setCurrentlyPlacingAgent(std::string text);

	~GraphicView(void);
};

#endif

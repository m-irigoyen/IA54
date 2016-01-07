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
#include "Utilities/FilePaths.h"

#define RECEPTOR_RADIUSSIZE 6
#define EMITTER_RADIUSSIZE 6
#define WAVE_SIZE 2

#define WAVE_AMPLITUDE_MAX 100	// Threshold used for making wave transparent with attenuation

#define HELPWINDOW_WIDTH 400
#define HELPWINDOW_HEIGHT 400

using namespace std;

/*
*   The GraphicView handles the GUI, drawing and displaying, etc.
*/
class GraphicView
{

public:
	GraphicView();

	void Init(int width, int height, int problemWidth, int problemHeight, Problem* problem);		// Init the window
	void Draw();							// Draw stuff
	void clean();	// Cleans the graphics stuff

	void drawHelpWindow();

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
	void setCurrentlyPlacingAgent(std::string text, int colorCode);
	void resetText();
	void setBrainActive(bool active);

	void setIsTerrainEditor(bool isTerrainEditor);

	~GraphicView(void);

private:
	sf::RenderWindow* window;			// The window
	sf::RenderWindow* problemWindow;	// The problem's window
	sf::RenderWindow* helpWindow;		// Helper window
	bool isTerrainEditor;

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

	bool brainActive;

	// Used to compute the alpha component of waves
	float maxAmplitude;

	PROBLEM_TYPE problemType;

	void toggle(bool& toToggle);

	vector<sf::Font> fonts;

	//GUI
	sf::Text text;
	sf::Text textBebasNeue;
	sf::Text placingAgentText;	// Data given by the simulator

								//Color code for the emitters
	sf::Color getColorCode(int emitterType);

};

#endif

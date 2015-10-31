#include "GraphicView.h"


void GraphicView::toggle(bool & toToggle)
{
	if (toToggle)
		toToggle = false;
	else
		toToggle = true;
}

GraphicView::GraphicView() : displayEmitters(true), displayReceptors(true), displayWaves(true), maxAmplitude(100), displaySimulator(true), displayProblem(true), problem(NULL), displayWaveOpacity(true)
{
}

void GraphicView::Init(int width, int height, Problem* problem)
{
	this->window = new sf::RenderWindow(sf::VideoMode(width, height), "IA54 - WaveAgents simulator");
	this->window->setVerticalSyncEnabled(false);
	this->window->setPosition(sf::Vector2i(0, 0));

	// Loading fonts
	sf::Font temp;
	if (!temp.loadFromFile("../Project/res/Fonts/ForcedSquare.ttf"))
	{
		cout << "GraphicView::Init : ERROR : couldn't load ForcedSquare font" << endl;
	}

	this->fonts.push_back(temp);

	// Init problem
	this->problemWindow = new sf::RenderWindow(sf::VideoMode(width, height), "IA54 - WaveAgents problem");
	this->problemWindow->setVerticalSyncEnabled(false);
	this->problemWindow->setPosition(sf::Vector2i(width, 0));

	this->setProblem(problem);

	this->problem->initGraphics(&this->fonts);
}

void GraphicView::Draw()
{
	window->clear(sf::Color::Black);
	problemWindow->clear(sf::Color::Black);

	if (this->displaySimulator)
	{
		// The shape to draw with
		sf::CircleShape circle;

		// DISPLAYING RECEPTORS
		if (this->displayReceptors)
		{
			// Updating color and radius
			circle.setRadius(RECEPTOR_RADIUSSIZE);
			circle.setFillColor(sf::Color(255, 0, 0));
			circle.setOrigin(RECEPTOR_RADIUSSIZE, RECEPTOR_RADIUSSIZE);

			// For each emitter in the world
			std::vector<BodyReceptor*>* worldReceptors = this->world->getReceptors();
			for (std::vector<BodyReceptor*>::iterator it = worldReceptors->begin(); it != worldReceptors->end(); ++it)
			{
				std::vector<float> pos = (*it)->GetPosition();	// Getting position
				circle.setPosition(pos[0], pos[1]);				// Placing wave accordingly on screen
				window->draw(circle);							// Drawing
			}
		}

		// DISPLAYING EMIITERS
		if (this->displayEmitters)
		{
			// Updating color and radius
			circle.setRadius(EMITTER_RADIUSSIZE);
			circle.setFillColor(sf::Color(0, 255, 0));
			circle.setOrigin(EMITTER_RADIUSSIZE, EMITTER_RADIUSSIZE);

			// For each emitter in the world
			std::vector<BodyEmitter*>* worldEmitters = this->world->getEmitters();
			for (std::vector<BodyEmitter*>::iterator it = worldEmitters->begin(); it != worldEmitters->end(); ++it)
			{
				std::vector<float> pos = (*it)->GetPosition();	// Getting position
				circle.setPosition(pos[0], pos[1]);				// Placing wave accordingly on screen
				window->draw(circle);							// Drawing
			}
		}

		// DISPLAYING WAVES
		if (this->displayWaves)
		{
			// Updating color
			circle.setFillColor(sf::Color::Transparent);
			circle.setOutlineThickness(1);
			// For each wave in the world
			std::vector<Wave*>* worldWaves = this->world->getWaves();
			for (std::vector<Wave*>::iterator it = worldWaves->begin(); it != worldWaves->end(); ++it)
			{
				double rad = (*it)->getRadius();
				circle.setRadius(rad);				// Setting radius
				circle.setOrigin(rad, rad);	// Setting new origin

				if (this->displayWaveOpacity)
				{
					// Displaying the wave's fade away
					double ampl = (*it)->getAmplitude();
					if (ampl > WAVE_AMPLITUDE_MAX)	// Capping to the threshold if amplitude is too high
						ampl = WAVE_AMPLITUDE_MAX;
					circle.setOutlineColor(sf::Color(255, 255, 255, (ampl * 255)/WAVE_AMPLITUDE_MAX));
				}

				std::vector<float> pos = (*it)->GetPosition();	// Getting position
				circle.setPosition(pos[0], pos[1]);				// Placing wave accordingly on screen
				
				window->draw(circle);							// Drawing
			}
		}

		// Displaying the whole thing
		window->display();
	}

	// Drawing the problem
	if (this->displayProblem)
	{
		this->problem->draw(this->problemWindow, &this->fonts);
		this->problemWindow->display();
	}
}

void GraphicView::setDisplayWaves(bool displayWaves)
{
	this->displayWaves = displayWaves;
}

void GraphicView::setDisplayEmitters(bool display)
{
	this->displayEmitters = display;
}

void GraphicView::setDisplayReceptors(bool display)
{
	this->displayReceptors = display;
}

void GraphicView::setMaxAmplitude(float amplitude)
{
	this->maxAmplitude = amplitude;
}

void GraphicView::toggleDisplayWaves()
{
	this->toggle(this->displayWaves);
}

void GraphicView::toggleDisplayReceptors()
{
	this->toggle(this->displayReceptors);
}

void GraphicView::toggleDisplayEmitters()
{
	this->toggle(this->displayEmitters);
}

void GraphicView::toggleDisplaySimulator()
{
	this->toggle(this->displaySimulator);
	if (!this->displaySimulator)
		this->window->clear();
}

void GraphicView::toggleDisplayProblem()
{
	this->toggle(this->displayProblem);
	if (!this->displayProblem)
		this->problemWindow->clear();
}

void GraphicView::SetWorld(World* world)
{
	this->world = world;
}

void GraphicView::setProblem(Problem * problem)
{
	this->problem = problem;
}

void GraphicView::setProblemType(PROBLEM_TYPE type)
{
	this->problemType = type;
}

sf::RenderWindow* GraphicView::getWindow()
{
	return this->window;
}

GraphicView::~GraphicView(void)
{
	this->window->clear();
	delete this->window;
}

#include "GraphicView.h"


void GraphicView::toggle(bool & toToggle)
{
	if (toToggle)
		toToggle = false;
	else
		toToggle = true;
}

GraphicView::GraphicView() : displayEmitters(true), displayReceptors(true), displayWaves(true), maxAmplitude(100), displaySimulator(true), displayProblem(true), problem(NULL), displayWaveOpacity(true), problemWindow(NULL), window(NULL)
{
}

void GraphicView::Init(int width, int height, int problemWidth, int problemHeight, Problem* problem)
{
	if (this->window != NULL)
		this->window->close();
	this->window = new sf::RenderWindow(sf::VideoMode(width, height), "IA54 - WaveAgents simulator");
	this->window->setVerticalSyncEnabled(false);
	this->window->setPosition(sf::Vector2i(0, 0));

	if (!this->fonts.empty())
		this->fonts.clear();

	// Loading fonts
	sf::Font temp;
	if (!temp.loadFromFile("../Project/res/Fonts/ForcedSquare.ttf"))
	{
		cout << "GraphicView::Init : ERROR : couldn't load ForcedSquare font" << endl;
	}

	this->fonts.push_back(temp);

	// Text
	this->text.setFont(this->fonts.at(0));
	this->text.setCharacterSize(20);
	this->text.setColor(sf::Color::White);
	
	this->placingAgentText.setFont(this->fonts.at(0));
	this->placingAgentText.setCharacterSize(20);
	this->placingAgentText.setColor(sf::Color::White);

	// Init problem
	if (this->problemWindow != NULL)
		this->problemWindow->close();

	this->problemWindow = new sf::RenderWindow(sf::VideoMode(problemWidth, problemHeight), "IA54 - WaveAgents problem");
	this->problemWindow->setVerticalSyncEnabled(false);
	this->problemWindow->setPosition(sf::Vector2i(width, 0));

	this->setProblem(problem);

	this->problem->initGraphics(&this->fonts);
}

void GraphicView::Draw()
{
	if (this->window != NULL)
	{
		window->clear(sf::Color::Black);
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
					circle.setPosition(static_cast<float>(pos[0]), static_cast<float>(pos[1]));				// Placing wave accordingly on screen
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
					circle.setPosition(static_cast<float>(pos[0]), static_cast<float>(pos[1]));				// Placing wave accordingly on screen
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
					float rad = (*it)->getRadius();
					circle.setRadius(rad);				// Setting radius
					circle.setOrigin(rad, rad);	// Setting new origin

					if (this->displayWaveOpacity)
					{
						// Displaying the wave's fade away
						float ampl = (*it)->getAmplitude();
						if (ampl > (this->problem->getWaveAmplitudeOffset() + this->problem->getWaveAmplitudeRange()))	// Capping to the threshold if amplitude is too high
							ampl = this->problem->getWaveAmplitudeOffset() + this->problem->getWaveAmplitudeRange();
						circle.setOutlineColor(sf::Color(255, 255, 255, (ampl * 255) / (this->problem->getWaveAmplitudeOffset() + this->problem->getWaveAmplitudeRange())));
					}

					std::vector<float> pos = (*it)->GetPosition();	// Getting position
					circle.setPosition(pos[0], pos[1]);				// Placing wave accordingly on screen

					window->draw(circle);							// Drawing
				}
			}

			// Displaying GUI
			this->placingAgentText.setPosition(10, window->getSize().y - 30);
			window->draw(this->placingAgentText);

			// Displaying the whole thing
			window->display();
		}
	}

	if (this->problemWindow != NULL)
	{
		problemWindow->clear(sf::Color::Black);
		// Drawing the problem
		if (this->displayProblem)
		{
			this->problem->draw(this->problemWindow);
			this->problemWindow->display();
		}
	}
}

void GraphicView::clean()
{
	this->problem = NULL;
	this->world = NULL;

	this->fonts.clear();
	
	this->window->clear();
	delete (this->window);
	this->problemWindow->clear();
	delete (this->problemWindow);
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

void GraphicView::setCurrentlyPlacingAgent(std::string text)
{
	this->placingAgentText.setString ("Currently placing : " + text);
}

GraphicView::~GraphicView(void)
{
	this->window->clear();
	delete this->window;
}

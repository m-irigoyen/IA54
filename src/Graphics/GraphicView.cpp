#include "GraphicView.h"


void GraphicView::toggle(bool & toToggle)
{
	if (toToggle)
		toToggle = false;
	else
		toToggle = true;
}

sf::Color GraphicView::getColorCode(int emitterType)
{
	switch (emitterType)
	{
	case 1 :
		return sf::Color::Green;
	case 2:
		return sf::Color::Blue;
	case 3:
		return sf::Color::Cyan;
	case 4:
		return sf::Color::Magenta;
	case 5:
		return sf::Color::Yellow;
	default : 
		return sf::Color::Red;
	}
}

GraphicView::GraphicView() : displayEmitters(true), displayReceptors(true), displayWaves(true), maxAmplitude(100), displaySimulator(true), displayProblem(true), problem(NULL), displayWaveOpacity(true), problemWindow(NULL), window(NULL), helpWindow(NULL), brainActive(false)
{
}

void GraphicView::Init(int width, int height, int problemWidth, int problemHeight, Problem* problem)
{
	if (this->window != NULL)
	{
		//this->window->close();
		this->window->setSize(sf::Vector2u(width, height));
		this->window->setVerticalSyncEnabled(false);
	}
	else
	{
		this->window = new sf::RenderWindow(sf::VideoMode(width, height), "IA54 - WaveAgents simulator");
		this->window->setVerticalSyncEnabled(false);
		this->window->setPosition(sf::Vector2i(0, 0));
	}

	if (this->helpWindow != NULL)
	{
		this->helpWindow->setSize(sf::Vector2u(HELPWINDOW_WIDTH, HELPWINDOW_HEIGHT));
		this->helpWindow->setVerticalSyncEnabled(false);
	}
	else
	{
		this->helpWindow = new sf::RenderWindow(sf::VideoMode(HELPWINDOW_WIDTH, HELPWINDOW_HEIGHT), "IA54 - helper window");
		this->helpWindow->setVerticalSyncEnabled(false);
		this->helpWindow->setPosition(sf::Vector2i(0, 400));
	}

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
	{
		//this->window->close();
		this->problemWindow->setSize(sf::Vector2u(problemWidth, problemHeight));
		this->problemWindow->setVerticalSyncEnabled(false);
	}
	else
	{
		this->problemWindow = new sf::RenderWindow(sf::VideoMode(problemWidth, problemHeight), "IA54 - WaveAgents problem");
		this->problemWindow->setVerticalSyncEnabled(false);
		this->problemWindow->setPosition(sf::Vector2i(width, 0));
	}

	this->setProblem(problem);

	this->problem->initGraphics(&this->fonts);
}

void GraphicView::Draw()
{
	if (this->helpWindow != NULL) {
		this->drawHelpWindow();
	}
		
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
				circle.setOrigin(RECEPTOR_RADIUSSIZE, RECEPTOR_RADIUSSIZE);

				// For each emitter in the world
				std::vector<BodyReceptor*>* worldReceptors = this->world->getReceptors();
				for (std::vector<BodyReceptor*>::iterator it = worldReceptors->begin(); it != worldReceptors->end(); ++it)
				{
					std::vector<float> pos = (*it)->GetPosition();	// Getting position
					circle.setPosition(static_cast<float>(pos[0]), static_cast<float>(pos[1]));				// Placing wave accordingly on screen
					circle.setFillColor(this->getColorCode((*it)->getBodyType()));
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
					circle.setFillColor(this->getColorCode((*it)->getBodyType()));
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
						circle.setOutlineColor(sf::Color(255, 255, 255, (ampl * 64) / (this->problem->getWaveAmplitudeOffset() + this->problem->getWaveAmplitudeRange())));
					}

					std::vector<float> pos = (*it)->GetPosition();	// Getting position
					circle.setPosition(pos[0], pos[1]);				// Placing wave accordingly on screen

					window->draw(circle);							// Drawing
				}
			}

			// Displaying GUI
			this->placingAgentText.setPosition(10, window->getSize().y - 30);
			window->draw(this->placingAgentText);

			// Drawing wave speed
			this->text.setString("waves x" + to_string(this->world->getWaveSpeed()));
			this->text.setColor(sf::Color::White);
			this->text.setPosition(window->getSize().x - 10 - this->text.getLocalBounds().width,
				10);
			window->draw(this->text);
			
			//Drawing brain active text
			if (this->brainActive)
			{
				this->text.setPosition(10, 10);
				this->text.setColor(sf::Color::Red);
				this->text.setString("Brain active");
				this->window->draw(this->text);
			}

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
	this->helpWindow->clear();
	delete (this->helpWindow);
}

void GraphicView::setHelpWindow(HELP_TYPE type)
{
	this->helpWindowIsSimulator = type;
}

void GraphicView::drawHelpWindow()
{
	float marginLeft = 20.0f, marginTop = 20.0f, verticalSpace = this->fonts.at(0).getLineSpacing(this->text.getCharacterSize()), letterSize = this->text.getCharacterSize();

	this->helpWindow->clear(sf::Color::Black);

	if (this->window->hasFocus())
	{
		//TODO : if : ces 3 lignes là t'affichent sur la bonne fenêtre. tu les copie colles pour chaque affichage en changeant la position et le texte
		
		this->text.setPosition(marginLeft,marginTop );
		this->text.setString("+- : Change wave speed");
		this->helpWindow->draw(this->text);


		this->text.setPosition(marginLeft, marginTop + verticalSpace + letterSize);
		this->text.setString("F1 : Launch level editor");
		this->helpWindow->draw(this->text);

		this->text.setPosition(marginLeft, marginTop + 2*verticalSpace + 2*letterSize);
		this->text.setString("F2 : Launch rocket one engine");
		this->helpWindow->draw(this->text);

		this->text.setPosition(marginLeft, marginTop + 3 * verticalSpace + 3 * letterSize);
		this->text.setString("F3 : Launch rocket two engines");
		this->helpWindow->draw(this->text);

		this->text.setPosition(marginLeft, marginTop + 4 * verticalSpace + 4 * letterSize);
		this->text.setString("0 -> 5 : place agents");
		this->helpWindow->draw(this->text);

		this->text.setPosition(marginLeft, marginTop + 5 * verticalSpace + 5 * letterSize);
		this->text.setString("B : toggle brain active");
		this->helpWindow->draw(this->text);

		this->text.setPosition(marginLeft, marginTop + 6 * verticalSpace + 6 * letterSize);
		this->text.setString("L Click : move agents");
		this->helpWindow->draw(this->text);

		this->text.setPosition(marginLeft, marginTop + 7 * verticalSpace + 7 * letterSize);
		this->text.setString("R Click : place agent");
		this->helpWindow->draw(this->text);

		this->text.setPosition(marginLeft, marginTop + 8 * verticalSpace + 8 * letterSize);
		this->text.setString("Del : delete selected agent");
		this->helpWindow->draw(this->text);

		this->text.setPosition(marginLeft, marginTop + 9 * verticalSpace + 9 * letterSize);
		this->text.setString("W : toggle display waves");
		this->helpWindow->draw(this->text);
		
	}
	else if(this->problemWindow->hasFocus())
	{
		this->text.setPosition(marginLeft, marginTop);
		this->text.setString("F4 -> F11 : load preset level");
		this->helpWindow->draw(this->text);


		this->text.setPosition(marginLeft, marginTop + verticalSpace + letterSize);
		this->text.setString("+- : Change speed");
		this->helpWindow->draw(this->text);

		this->text.setPosition(marginLeft, marginTop + 2 * verticalSpace + 2 * letterSize);
		this->text.setString("P : Pause problem");
		this->helpWindow->draw(this->text);

		this->text.setPosition(marginLeft, marginTop + 3 * verticalSpace + 3 * letterSize);
		this->text.setString("R : reset rocket position");
		this->helpWindow->draw(this->text);

		this->text.setPosition(marginLeft, marginTop + 4 * verticalSpace + 4 * letterSize);
		this->text.setString("Ctrl + LClick : set rocket position");
		this->helpWindow->draw(this->text);

		this->text.setPosition(marginLeft, marginTop + 5 * verticalSpace + 5 * letterSize);
		this->text.setString("TAB : toggle show hud");
		this->helpWindow->draw(this->text);

		this->text.setPosition(marginLeft, marginTop + 6 * verticalSpace + 6 * letterSize);
		this->text.setString("U : toggle user control (arrows)");
		this->helpWindow->draw(this->text);

		this->text.setPosition(marginLeft, marginTop + 7 * verticalSpace + 7 * letterSize);
		this->text.setString("T : clear trajectories");
		this->helpWindow->draw(this->text);

		this->text.setPosition(marginLeft, marginTop + 8 * verticalSpace + 8 * letterSize);
		this->text.setString("A : toggle relative/fixed angle");
		this->helpWindow->draw(this->text);

		this->text.setPosition(marginLeft, marginTop + 9 * verticalSpace + 9 * letterSize);
		this->text.setString("L : Load specific level (console)");
		this->helpWindow->draw(this->text);
	}
	else
	{
		this->text.setPosition(marginLeft, marginTop);
		this->text.setString("Ceci est la fenêtre d'aide.");
		this->helpWindow->draw(this->text);
	}

	this->helpWindow->display();
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

void GraphicView::setCurrentlyPlacingAgent(std::string text, int colorCode)
{
	this->placingAgentText.setString ("Currently placing : " + text);
	this->placingAgentText.setColor(this->getColorCode(colorCode));
}

void GraphicView::resetText()
{
	this->placingAgentText.setString("");
	this->text.setString("");
}

void GraphicView::setBrainActive(bool active)
{
	this->brainActive = active;
}

GraphicView::~GraphicView(void)
{
	this->window->clear();
	delete this->window;
}

#include "GraphicView.h"


void GraphicView::toggle(bool & toToggle)
{
	if (toToggle)
		toToggle = false;
	else
		toToggle = true;
}

GraphicView::GraphicView() : displayEmitters(true), displayReceptors(true), displayWaves(true), maxAmplitude(100), displaySimulator(true), displayProblem(true), problem(NULL)
{
}

void GraphicView::Init(int width, int height, Problem* problem)
{
	this->window = new sf::RenderWindow(sf::VideoMode(width, height), "IA54 - WaveAgents simulator");
	this->window->setVerticalSyncEnabled(false);

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

	this->setProblem(problem);

	this->problem->initGraphics(&this->fonts);
}

void GraphicView::Draw()
{
	window->clear(sf::Color::Black);
	problemWindow->clear(sf::Color::Black);

	if (this->displaySimulator)
	{
		//TODO: (optimise) change this. Really. Adding to a vector and clearing at each frame? Complexity goes through the roof
		// DISPLAYING RECEPTORS
		if (this->displayReceptors)
		{
			//Receptors
			std::vector<BodyReceptor*>* worldReceptors = this->world->getReceptors();
			if (this->receptors.size() != worldReceptors->size())
			{
				this->receptors.clear();
				for (int i = 0; i < worldReceptors->size(); ++i)
				{
					this->receptors.push_back(sf::CircleShape(RECEPTOR_RADIUSSIZE, 15));
					this->receptors.at(this->receptors.size() - 1).setFillColor(sf::Color(255, 0, 0));
					this->receptors.at(this->receptors.size() - 1).setOrigin(RECEPTOR_RADIUSSIZE, RECEPTOR_RADIUSSIZE);
				}
			}

			for (int idCurrentBody = 0; idCurrentBody < worldReceptors->size(); ++idCurrentBody)
			{
				std::vector<float> pos = worldReceptors->at(idCurrentBody)->GetPosition();
				this->receptors[idCurrentBody].setPosition(pos[0], pos[1]);
				window->draw(this->receptors[idCurrentBody]);
			}

			/*std::cout << "Receptor size : " << this->receptors.size() << std::endl;
			std::cout << "World Receptor size : " << worldReceptors->size() << std::endl;*/
		}

		// DISPLAYING EMIITERS
		if (this->displayEmitters)
		{
			//Emitters
			std::vector<BodyEmitter*>* worldEmitters = this->world->getEmitters();
			if (this->emitters.size() != worldEmitters->size())
			{
				this->emitters.clear();
				for (int i = 0; i < worldEmitters->size(); ++i)
				{
					this->emitters.push_back(sf::CircleShape(EMITTER_RADIUSSIZE));
					this->emitters.at(this->emitters.size() - 1).setFillColor(sf::Color(0, 255, 0));
					this->emitters.at(this->emitters.size() - 1).setOrigin(EMITTER_RADIUSSIZE, EMITTER_RADIUSSIZE);
				}
			}

			for (int idCurrentBody = 0; idCurrentBody < worldEmitters->size(); ++idCurrentBody)
			{
				std::vector<float> pos = worldEmitters->at(idCurrentBody)->GetPosition();
				this->emitters[idCurrentBody].setPosition(pos[0], pos[1]);
				window->draw(this->emitters[idCurrentBody]);
			}
			/*std::cout << "Emitter size : " << this->emitters.size() << std::endl;
			std::cout << "World Emitter size : " << worldEmitters->size() << std::endl;*/
		}

		// DISPLAYING WAVES
		if (this->displayWaves)
		{
			//Waves
			if (displayWaves)
			{
				std::vector<Wave*>* worldWaves = this->world->getWaves();
				if (this->waves.size() != worldWaves->size())
				{
					this->waves.clear();
					for (int i = 0; i < worldWaves->size(); ++i)
					{
						//this->waves.push_back(sf::CircleShape(WAVE_SIZE));

						sf::CircleShape newWave(0.0f);
						// Setting color
						newWave.setFillColor(sf::Color(255, 255, 255, 0));
						newWave.setOutlineColor(sf::Color(0, 0, 255, 255));
						newWave.setOutlineThickness(1);

						// Setting origin
						float x;
						float y;
						worldWaves->at(i)->GetPosition(x, y);
						newWave.setPosition(x, y);
						//			std::cout << "New wave origin : " << x << "," << y << endl;

						/*this->waves.at(this->waves.size() - 1).setFillColor(sf::Color(255, 255, 255, 1));
						this->waves.at(this->waves.size() - 1).setOutlineColor(sf::Color(0, 0, 255));*/

						this->waves.push_back(newWave);
					}
				}

				int cpt = 0;
				for (int idCurrentWave = 0; idCurrentWave < worldWaves->size(); ++idCurrentWave)
				{
					this->waves[idCurrentWave].setOrigin(worldWaves->at(idCurrentWave)->getRadius(), worldWaves->at(idCurrentWave)->getRadius());
					this->waves[idCurrentWave].setRadius(worldWaves->at(idCurrentWave)->getRadius());
					window->draw(this->waves[idCurrentWave]);

					/*std::cout << "Drawing a wave at " << this->waves[idCurrentWave].getPosition().x << "," << this->waves[idCurrentWave].getPosition().y <<
					", radius : " << this->waves[idCurrentWave].getRadius() << std::endl;*/
					++cpt;
				}
				/*std::cout << "Wave size : " << this->waves.size() << std::endl;
				std::cout << "World Wave size : " << worldWaves->size() << std::endl;*/
			}
		}
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
}

void GraphicView::toggleDisplayProblem()
{
	this->toggle(this->displayProblem);
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

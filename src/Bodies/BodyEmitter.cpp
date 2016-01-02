#include "Bodies/BodyEmitter.h"

BodyEmitter::BodyEmitter(Semantic type, float x, float y) : Body(type,x,y), Emitter()
{
}

void BodyEmitter::initialise()
{

}


void BodyEmitter::update(sf::Time elapsedTime)
{
	// Go through the perceived objects list, and add a force for each of them
	for (Perception::BODY& b : this->perception.getPerceptions())
	{
		// TODO: add forces
		if (b.type.getSemantic().compare(Tags::receptor) == 0)
		{
			// its a receptor : aim to be at 30 pixels from it
			Vector v = Vector::getDirection(this->posX, this->posY, b.posX, b.posY);
			float d = v.length();

			v.normalise();
			if (d < 40.0f)
				v.invert();

			this->velocity.addForce(v, 1000);
		}
		else
		{
			//its an emitter : be repulsed by it
			Vector v = Vector::getDirection(b.posX, b.posY, this->posX, this->posY);
			float d = v.length()/40;
			this->velocity.addForce(v.normalise(), 100/d);
		}
	}

	if (elapsedTime.asSeconds() > 0.1f)
		elapsedTime = sf::seconds(0.1f);

	this->velocity.resolveForcesWithoutVelocity(elapsedTime.asSeconds());
	this->move(elapsedTime.asSeconds());
}

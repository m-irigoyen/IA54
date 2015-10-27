#include "ProblemRocket.h"


ProblemRocket::ProblemRocket() : Problem(), worldWidth(8000), worldHeight(6000), rocketX(4000), rocketY(3000), hasLanded(false), hasCrashed(false), hSpeed(0.0), vSpeed(0.0), enginePower(0)
{
	this->setAngle(0);
}

bool ProblemRocket::collides(double x, double y)
{
	// First : check if the position collides with terrain
	if (y <= 0.0)
	{
		// Second : check if the speed and angle is correct
		return true;
	}
	else
		return false;
}

bool ProblemRocket::correctLanding(double hSpeed, double vSpeed, int angle)
{
	if (angle == ANGLE_OFFSET)
	{
		if (hSpeed >= -20.0f && hSpeed <= 20.0f)
		{
			if (vSpeed <= 40.0f && vSpeed >= 0.0f)
			{
				cout << "Rocket landed successfully!" << endl;
				return true;
			}
			else
				cout << "Rocket crashed : verticalSpeed was too big!" << endl;
		}
		else
			cout << "Rocket crashed : horizontalSpeed was too big!" << endl;
	}
	else
		cout << "Rocket crashed : angle was different than 0!" << endl;
	return false;
}

void ProblemRocket::getThrustersForce(int angle, int power, double & horizontalForce, double & verticalForce)
{
	double vecX = cos(degToRad(angle));
	double vecY = sin(degToRad(angle));

	//cout << "Thruster computation : " << vecX << "," << vecY << endl;

	horizontalForce = (power*THRUSTER_STRENGTH*vecX) / 100;
	verticalForce = (power*THRUSTER_STRENGTH*vecY) / 100;

	//cout << "V : " << verticalForce << endl;
}

void ProblemRocket::run(sf::Time elapsedTime)
{
	if (!hasLanded && !hasCrashed)
	{
		double hOffset, vOffset;
		getThrustersForce(this->rocketAngle, this->enginePower, hOffset, vOffset);

		hSpeed += hOffset * elapsedTime.asSeconds();
		vSpeed += vOffset * elapsedTime.asSeconds() - (MARS_GRAVITY*elapsedTime.asSeconds());


		this->rocketY += vSpeed * elapsedTime.asSeconds();
		this->rocketX += hSpeed * elapsedTime.asSeconds();

		//cout << hSpeed << " / " << vSpeed << endl;

		// If collides with terrain
		if (this->collides(rocketX, rocketY))
		{
			// If is on flat zone
			if (1)
			{
				if (this->correctLanding(hSpeed, vSpeed, rocketAngle))
					this->hasLanded = true;
				else
					this->hasCrashed = true;
			}
			else
				this->hasCrashed = true;
		}
	}
	else
	{
		
	}
}

// Draw the problem
void ProblemRocket::draw(sf::RenderWindow * problemWindow)
{
	// Drawing terrain
	//TODO: draw the terrain

	// Drawing rocket
	this->rocketSprite.setPosition(rocketX*problemWindow->getSize().x / worldWidth, 
		problemWindow->getSize().y - (rocketY*problemWindow->getSize().y / worldHeight));
	this->rocketSprite.setRotation(-this->rocketAngle);

	problemWindow->draw(this->rocketSprite);
}

void ProblemRocket::init()
{
	//TODO: load rocket image and set sprite
	if (!this->rocketTexture.loadFromFile("../Project/res/Rocket.png"))
	{
		std::cout << "ProblemRocket::init : ERROR : couldn't load rocket image from disk." << std::endl;
	}
	this->rocketSprite.setTexture(rocketTexture);
	this->rocketSprite.setOrigin(rocketTexture.getSize().x/2, rocketTexture.getSize().y/2);
}

void ProblemRocket::setPower(int power)
{
	if (power > 100)
		power = 100;
	else if (power < 0)
		power = 0;
	this->enginePower = power;
}

void ProblemRocket::addPower(int powerOffset)
{
	this->setPower(this->enginePower + powerOffset);
}

void ProblemRocket::setAngle(int angle)
{
	angle += ANGLE_OFFSET;	// Applying offset to have 0° be up
	while (angle >= 360)
		angle -= 360;
	while (angle < 0)
		angle += 360;
	this->rocketAngle = angle;
}

void ProblemRocket::addAngle(int angleOffset)
{
	this->setAngle(this->rocketAngle + angleOffset);
}

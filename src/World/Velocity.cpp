#include "Velocity.h"


Velocity::Velocity() : m_for_x(0.0f), m_for_y(0.0f), m_vel_x(0.0f), m_vel_y(0.0f), maxVelocity(500.0f)
{
}


Velocity::~Velocity()
{
}

void Velocity::addXForce(float xForce)
{
	m_for_x += xForce;
}

void Velocity::addYForce(float yForce)
{
	m_for_x -= yForce;
}

void Velocity::addForce(Vector v, float unit)
{
	this->addForce(v.getX() * unit, v.getY() * unit);
}

void Velocity::addForce(float xForce, float yForce)
{
	m_for_x += xForce;
	m_for_y += yForce;
}

void Velocity::tendToRestX(float deceleration)
{
	if (deceleration < 0)
	{
		deceleration = deceleration * (-1);
	}
	if (m_vel_x < 0)
	{
		m_vel_x += deceleration;
		if (m_vel_x > 0)
			m_vel_x = 0.0f;
	}
	else if (m_vel_x > 0)
	{
		m_vel_x -= deceleration;
		if (m_vel_x < 0)
			m_vel_x = 0.0f;
	}
}

void Velocity::tendToX(float targetVelocity, double factor)
{
	/*if (targetVelocity == 0.0f)
		tendToRestX();
	else
		addXForce((targetVelocity / 60) * factor);*/
	//TODO: tricky stuff
}

void Velocity::tendToY(float targetVelocity, double factor)
{
	//TODO: tricky stuff
}

void Velocity::tendTo(bool x, float factor)	
{
	//TODO: tricky stuff.
}

void Velocity::tendTo(float x, float y, float factor)
{
	//TODO: tricky stuff.
}

void Velocity::resolveForces(float dt, bool applyGravity)
{
	// converting forces in velocity
	m_vel_x += m_for_x*dt;
	if (applyGravity)
		m_vel_y += m_for_y*dt + GRAVITY*dt;
	else
		m_vel_y += m_for_y*dt;

	// Checking velocity issues
	if (m_vel_x < -maxVelocity)
		m_vel_x = -maxVelocity;
	else if (m_vel_x > maxVelocity)
		m_vel_x = maxVelocity;

	if (m_vel_y < -maxVelocity)
		m_vel_y = -maxVelocity;
	else if (m_vel_y > maxVelocity)
		m_vel_y = maxVelocity;

	// resetting forces
	m_for_x = 0.0f;
	m_for_y = 0.0f;
}

void Velocity::resolveForcesWithoutVelocity(float dt)
{
	this->m_vel_x = 0.0f;
	this->m_vel_y = 0.0f;
	this->resolveForces(dt);
}

bool Velocity::immobile()
{
	if (m_vel_x == 0.0f && m_vel_y == 0.0f && m_for_x == 0.0f && m_for_y == 0.0f)
		return true;
	return false;
}

void Velocity::setVelocity(float xVelocity, float yVelocity)
{
	m_vel_x = xVelocity;
	m_vel_y = yVelocity;
}

void Velocity::setXVelocity(float xVelocity)
{
	m_vel_x = xVelocity;
}

void Velocity::setYVelocity(float yVelocity)
{
	m_vel_y = yVelocity;
}

void Velocity::setForce(float xForce, float yForce)
{
	m_for_x = xForce;
	m_for_y = yForce;
}

void Velocity::getVelocity(float& xVelocity, float& yVelocity)
{
	if (xVelocity != NULL)
		xVelocity = m_vel_x;
	if (yVelocity != NULL)
		yVelocity = m_vel_y;
}

Vector Velocity::getVelocity()
{
	return Vector(this->m_vel_x, this->m_vel_y);
}

float Velocity::getYVelocity()
{
	return m_vel_y;
}

float Velocity::getXVelocity()
{
	return m_vel_x;
}

void Velocity::getForce(float& xVelocitys, float& yVelocitys)
{
	if (xVelocitys != NULL)
		xVelocitys = m_for_x;
	if (yVelocitys != NULL)
		yVelocitys = m_for_y;
}

Vector Velocity::getForce()
{
	return Vector(this->m_for_x, this->m_for_y);
}

Vector Velocity::getDirection()
{
	return Vector::normalised(this->getVelocity());
}

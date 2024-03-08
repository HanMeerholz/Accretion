#include "asteroid.h"

using namespace Tmpl8;

namespace Accretion
{
	Asteroid::Asteroid()
	{}

	Asteroid::Asteroid(Tmpl8::vec2 position, float radius)
		: position(position), radius(radius)
	{}

	vec2 Asteroid::getPosition()
	{
		return position;
	}

	void Asteroid::setPosition(vec2 position)
	{
		this->position = position;
	}

	bool Asteroid::isDestroyed()
	{
		return destroyed;
	}

	void Asteroid::setDestroyed()
	{
		destroyed = true;
	}

	float Asteroid::getRadius()
	{
		return radius;
	}

	void Asteroid::draw(Surface* const screen)
	{
		screen->Circle(position.x, position.y, radius, WHITE);
	}
}
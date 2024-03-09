#include "asteroid.h"

using namespace Tmpl8;

namespace Accretion
{
	Asteroid::Asteroid()
	{}

	Asteroid::Asteroid(Tmpl8::vec2 position, float radius)
		: GameObject(position, radius)
	{}

	void Asteroid::draw(Surface* const screen)
	{
		vec2 position = getPosition();
		screen->Circle(position.x, position.y, getRadius(), WHITE);
	}
}
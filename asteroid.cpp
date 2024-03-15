#include "asteroid.h"
#include "spritedgameobject.h"
#include <iostream>

using namespace Tmpl8;

namespace Accretion
{
	Asteroid::Asteroid(Tmpl8::Sprite* const sprite)
		: SpritedGameObject(sprite)
	{}

	Asteroid::Asteroid(Tmpl8::Sprite* const sprite, Tmpl8::vec2 position, float radius)
		: SpritedGameObject(sprite, position, radius)
	{}

	Asteroid::Asteroid(Tmpl8::Sprite* const sprite, Tmpl8::vec2 position, float radius, Tmpl8::vec2 velocity)
		: Asteroid(sprite, position, radius)
	{
		this->velocity = velocity;
	}

	void Asteroid::draw(Surface* const screen)
	{
		vec2 position = getPosition();
		screen->Circle(position.x, position.y, getRadius(), WHITE);
	}

	void Asteroid::update(BlackHole& blackHole)
	{
		setPosition(getPosition() + velocity);
		float force = blackHole.getMass() / powf(distance(blackHole), 2.0f) * gravity;

		vec2 direction = (blackHole.getPosition() - getPosition()).normalized();

		velocity += {force * direction.x, force * direction.y};
	}
	float Asteroid::calculateRadius(float mass)
	{
		return cbrtf(mass / (2 / 3 * TAU * density));
	}
}
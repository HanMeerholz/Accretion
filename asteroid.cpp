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

	void Asteroid::draw(Tmpl8::Surface* const screen, float currentTime)
	{
		SpritedGameObject::draw(screen, currentTime);
	}

	void Asteroid::draw(Surface* const screen)
	{
		vec2 leftTopPosition = getLeftTopPosition();
		float spriteRadius = getRadius() * 1.13f;
		sprite->DrawScaled((int)leftTopPosition.x, (int)leftTopPosition.y, (int)(2 * spriteRadius), (int)(2 * spriteRadius), screen);

		vec2 position = getPosition();
		screen->Circle(position.x, position.y, getRadius(), YELLOW);
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
	Tmpl8::vec2 Asteroid::getLeftTopPosition()
	{
		vec2 position = getPosition();
		float radius = getRadius();
		return { position.x - radius , position.y - radius };
	}
}
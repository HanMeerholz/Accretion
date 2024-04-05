#include "asteroid.h"
#include "spritedgameobject.h"
#include <iostream>

using namespace Tmpl8;

namespace Accretion
{
	Asteroid::Asteroid(Tmpl8::Sprite* const sprite, Tmpl8::vec2 position, float mass)
		: Asteroid(sprite, position, mass, { 0.0f, 0.0f })
	{}

	Asteroid::Asteroid(Tmpl8::Sprite* const sprite, Tmpl8::vec2 position, float mass, Tmpl8::vec2 velocity)
		: SpritedGameObject(sprite, position, mass), velocity(velocity)
	{
		radius = calculateRadius(mass);
		animationOffset = IRand(sprite->GetNumFrames());
		drawReverse = IRand(2);
		animationSpeed = Rand(8.0f, 30.0f);
	}

	void Asteroid::draw(Tmpl8::Surface* const screen, float currentTime)
	{
		SpritedGameObject::draw(screen, currentTime);
	}

	void Asteroid::draw(Surface* const screen)
	{
		vec2 leftTopPosition = getLeftTopPosition();
		float spriteRadius = radius * ASTEROID_SPRITE_RADIUS_FACTOR;
		sprite->DrawScaled((int)leftTopPosition.x, (int)leftTopPosition.y, (int)(2 * spriteRadius), (int)(2 * spriteRadius), screen);

		// screen->Circle(position.x, position.y, radius, YELLOW);
	}

	void Asteroid::update(BlackHole& blackHole)
	{
		GameObject::update();

		if (!blackHole.isDestroyed()) {
			float force = mass * blackHole.getMass() / powf(distance(blackHole), 2.0f) * GRAVITATIONAL_CONSTANT;
			float acceleration = force / mass;
			vec2 direction = (blackHole.getPosition() - getPosition()).normalized();
			velocity += {acceleration* direction.x, acceleration* direction.y};
		}

		position += velocity;

		if (position.x < -2 * ScreenWidth || position.x > 3 * ScreenWidth || position.y < -2 * ScreenHeight || position.y > 3 * ScreenWidth) {
			setDestroyed();
		}
	}

	float Asteroid::calculateRadius(float mass)
	{
		return cbrtf(mass / (2.0f / 3.0f * TAU * density));
	}

	Tmpl8::vec2 Asteroid::getLeftTopPosition()
	{
		return { position.x - radius , position.y - radius };
	}
}
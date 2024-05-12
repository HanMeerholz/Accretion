#include "asteroid.h"
#include "spaceObject.h"
#include <iostream>

using namespace Tmpl8;

namespace Accretion
{
	Asteroid::Asteroid(Tmpl8::Sprite* const sprite, Tmpl8::vec2 position, float mass, Tmpl8::vec2 velocity)
		: SpaceObject(sprite, position, Rand(8.0f, 30.0f), (int)Rand((float)sprite->GetNumFrames()), IRand(2), mass), velocity(velocity)
	{
		radius = calculateRadius(mass);
		dimensions = { radius * 2, radius * 2 };
	}

	void Asteroid::update(BlackHole& blackHole, float deltaTime)
	{
		update(deltaTime);

		// apply gravity
		if (!blackHole.isDestroyed()) {
			float force = mass * blackHole.getMass() / powf(distanceTo(blackHole), 2.0f) * GRAVITATIONAL_CONSTANT;
			float acceleration = force / mass;
			vec2 direction = (blackHole.getPosition() - getPosition()).normalized();
			velocity += {acceleration * direction.x * deltaTime, acceleration * direction.y * deltaTime};
		}

		position += velocity * deltaTime;

		// if the asteroid ever gets more than a screen away, it is destroyed
		if (position.x < -ScreenWidth || position.x > 2 * ScreenWidth || position.y < -ScreenHeight || position.y > 2 * ScreenWidth) {
			destroy();
		}
	}

	void Asteroid::update(float deltaTime)
	{
		SpaceObject::update(deltaTime);
	}

	void Asteroid::draw(Surface* const screen)
	{
		vec2 topLeftPosition = getTopLeftPosition();

		int curFrame = (int)(animationProgress * sprite->GetNumFrames());
		sprite->SetFrame(curFrame);

		float spriteRadius = radius * SPRITE_RADIUS_FACTOR;
		sprite->DrawScaled((int)topLeftPosition.x, (int)topLeftPosition.y, (int)(2 * spriteRadius), (int)(2 * spriteRadius), screen);
	}

	float Asteroid::calculateRadius(float mass)
	{
		// tau is better than pi (don't @ me)
		return cbrtf(mass / (2.0f / 3.0f * TAU * density));
	}
}
#include "blackhole.h"
#include "surface.h"

using namespace Tmpl8;

namespace Accretion
{
	BlackHole::BlackHole(Sprite* const sprite) :
		sprite(sprite),
		animationLength(sprite->GetNumFrames() / animationSpeed)
	{
		setRadius(calculateRadius(mass));
	}

	BlackHole::~BlackHole()
	{
		delete sprite;
	}

	float BlackHole::getMass()
	{
		return mass;
	}

	void BlackHole::addMass(float mass)
	{
		this->mass += mass;
	}

	void BlackHole::moveUp()
	{
		vec2 position = getPosition();
		setPosition({position.x, position.y - speed});
	}

	void BlackHole::moveDown()
	{
		vec2 position = getPosition();
		setPosition({ position.x, position.y + speed });
	}

	void BlackHole::moveLeft()
	{
		vec2 position = getPosition();
		setPosition({ position.x - speed, position.y });
	}

	void BlackHole::moveRight()
	{
		vec2 position = getPosition();
		setPosition({ position.x + speed, position.y });
	}

	void BlackHole::update()
	{
		if (isDestroyed()) return;

		mass *= 1 - massLossRate;
		if (mass < criticalMass) setDestroyed();

		setRadius(calculateRadius(mass));
	}

	float BlackHole::calculateRadius(float mass)
	{
		return mass * BlackHole::metersPerSolarMass;
	}

	void BlackHole::consumeAsteroid(Asteroid& asteroid)
	{
		asteroid.setDestroyed();
		addMass(0.0001f * asteroid.getRadius());
	}

	void BlackHole::draw(Tmpl8::Surface* const screen, float const currentTime)
	{
		int curFrame = (float)(fmod(currentTime, animationLength) / animationLength) * sprite->GetNumFrames();
		sprite->SetFrame(curFrame);
		draw(screen);
	}

	void BlackHole::draw(Tmpl8::Surface* const screen)
	{
		vec2 leftTopPosition = getLeftTopPosition();
		float radius = getRadius();
		sprite->DrawScaled(leftTopPosition.x, leftTopPosition.y, 2 * radius, 2 * radius, screen);
	}

	vec2 BlackHole::getLeftTopPosition()
	{
		vec2 position = getPosition();
		float radius = getRadius();
		return { position.x - radius , position.y - radius };
	}
}
#include "blackhole.h"
#include "surface.h"

using namespace Tmpl8;

namespace Accretion
{
	BlackHole::BlackHole(Sprite* const sprite) :
		SpritedGameObject(sprite)
	{
		setRadius(calculateRadius(mass));
		setPosition(startPosition);
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
		position.y = Modulo(position.y - speed, ScreenHeight);
		setPosition(position);
	}

	void BlackHole::moveDown()
	{
		vec2 position = getPosition();
		position.y = Modulo(position.y + speed, ScreenHeight);
		setPosition(position);
	}

	void BlackHole::moveLeft()
	{
		vec2 position = getPosition();
		position.x = Modulo(position.x - speed, ScreenWidth);
		setPosition(position);
	}

	void BlackHole::moveRight()
	{
		vec2 position = getPosition();
		position.x = Modulo(position.x + speed, ScreenWidth);
		setPosition(position);
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

	void BlackHole::draw(Tmpl8::Surface* const screen, float currentTime)
	{
		SpritedGameObject::draw(screen, currentTime);
	}

	void BlackHole::draw(Tmpl8::Surface* const screen)
	{
		vec2 leftTopPosition = getLeftTopPosition();
		float radius = getRadius();
		sprite->DrawScaledWrapAround((int) leftTopPosition.x, (int) leftTopPosition.y, (int) (2 * radius), (int) (2 * radius), screen);

		vec2 position = getPosition();
		screen->Circle(position.x, position.y, getRadius(), YELLOW);
	}

	vec2 BlackHole::getLeftTopPosition()
	{
		vec2 position = getPosition();
		float radius = getRadius();
		return { position.x - radius , position.y - radius };
	}
}
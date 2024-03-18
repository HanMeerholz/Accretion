#include "blackhole.h"
#include "surface.h"

using namespace Tmpl8;

namespace Accretion
{
	BlackHole::BlackHole(Sprite* const sprite) :
		SpritedGameObject(sprite, BLACK_HOLE_START_POSITION, BLACK_HOLE_START_MASS)
	{
		radius = calculateRadius(mass);
	}

	void BlackHole::addMass(float mass)
	{
		this->mass += mass;
	}

	void BlackHole::moveUp()
	{
		position.y = Modulo(position.y - speed, ScreenHeight);
	}

	void BlackHole::moveDown()
	{
		position.y = Modulo(position.y + speed, ScreenHeight);
	}

	void BlackHole::moveLeft()
	{
		position.x = Modulo(position.x - speed, ScreenWidth);
	}

	void BlackHole::moveRight()
	{
		position.x = Modulo(position.x + speed, ScreenWidth);
	}

	void BlackHole::update()
	{
		GameObject::update();
		if (destroyed) return;
		mass *= 1 - massLossRate;
		if (mass < criticalMass) setDestroyed();
	}

	float BlackHole::calculateRadius(float mass)
	{
		return mass * BlackHole::metersPerSolarMass;
	}

	void BlackHole::consumeAsteroid(Asteroid& asteroid)
	{
		asteroid.setDestroyed();
		addMass(asteroid.getMass());
	}

	void BlackHole::draw(Tmpl8::Surface* const screen, float currentTime)
	{
		SpritedGameObject::draw(screen, currentTime);
	}

	void BlackHole::draw(Tmpl8::Surface* const screen)
	{
		vec2 leftTopPosition = getLeftTopPosition();
		sprite->DrawScaledWrapAround((int) leftTopPosition.x, (int) leftTopPosition.y, (int) (2 * radius), (int) (2 * radius), screen);

		screen->Circle(position.x, position.y, radius, YELLOW);
	}

	vec2 BlackHole::getLeftTopPosition()
	{
		return { position.x - radius , position.y - radius };
	}
}
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

	BlackHole::Direction BlackHole::getDirection()
	{
		return direction;
	}

	void BlackHole::setDirection(Direction direction)
	{
		this->direction = direction;
	}


	void BlackHole::addMass(float mass)
	{
		this->mass += mass;
	}

	void BlackHole::update()
	{
		GameObject::update();
		if (destroyed) return;

		vec2 directionVector;
		switch (direction) {
			case STILL: directionVector = { 0, 0 }; break;
			case LEFT: directionVector = { -1, 0 }; break;
			case LEFTUP: directionVector = vec2{ -1, -1 }.normalized(); break;
			case UP: directionVector = { 0, -1 }; break;
			case RIGHTUP: directionVector = vec2{ 1, -1 }.normalized(); break;
			case RIGHT: directionVector = { 1, 0 }; break;
			case RIGHTDOWN: directionVector = vec2{ 1, 1 }.normalized(); break;
			case DOWN: directionVector = { 0, 1 }; break;
			case LEFTDOWN: directionVector = vec2{ -1, 1 }.normalized(); break;
		}
		position += directionVector * speed;
		position.x = Modulo(position.x, ScreenWidth);
		position.y = Modulo(position.y, ScreenHeight);

		mass *= 1 - massLossRate;
		if (mass < criticalMass) setDestroyed();
	}

	float BlackHole::calculateRadius(float mass)
	{
		return mass * METERS_PER_EARTH_MASS;
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

		//screen->Circle(position.x, position.y, radius, YELLOW);
	}

	vec2 BlackHole::getLeftTopPosition()
	{
		return { position.x - radius , position.y - radius };
	}
}
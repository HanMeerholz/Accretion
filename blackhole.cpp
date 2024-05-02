#include "blackhole.h"
#include "surface.h"
#include "particleEffect.h"

using namespace Tmpl8;

namespace Accretion
{
	BlackHole::BlackHole(Sprite* const sprite, Sprite* const deathSprite) :
		SpritedGameObject(sprite, BLACK_HOLE_START_POSITION, BLACK_HOLE_START_MASS), deathSprite(deathSprite)
	{
		radius = calculateRadius(mass);
	}

	void BlackHole::setDirection(vec2 direction)
	{
		this->direction = direction;
	}


	void BlackHole::addMass(float mass)
	{
		this->mass += mass;
	}

	void BlackHole::update(float deltaTime)
	{
		GameObject::update(deltaTime);
		if (destroyed) return;

		switch (phase) {
			case ALIVE:
				position += direction * speed * deltaTime;
				position.x = Modulo(position.x, ScreenWidth);
				position.y = Modulo(position.y, ScreenHeight);

				// every second the mass shrinks by the massLossRate times the initial mass
				mass *= powf(1 - massLossRate, deltaTime);
				if (mass < criticalMass) phase = CRITICAL;
				break;
			case CRITICAL:
				mass -= 1000.0f * deltaTime;
				if (mass <= 0)
				{
					mass = 0;
					deathEffect = new ParticleEffect(deathSprite, position);
					phase = IMPLOSION;
				}
				break;
			case IMPLOSION:
				if (deathEffect->isFinished()) {
					phase = DEATH;
					setDestroyed();
				}
				break;
		}
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

	void BlackHole::setPhase(BlackHole::Phase phase)
	{
		this->phase = phase;
	}

	void BlackHole::draw(Tmpl8::Surface* const screen, float currentTime)
	{
		if (phase == IMPLOSION)
		{
			if (deathEffect->getStartTime() == 0.0f) {
				deathEffect->setStartTime(currentTime);
			}
			deathEffect->draw(screen, currentTime);
		}
		else if (phase != DEATH)
		{
			SpritedGameObject::draw(screen, currentTime);
		}
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
#include "blackhole.h"
#include "surface.h"
#include "particleEffect.h"

using namespace Tmpl8;

namespace Accretion
{
	BlackHole::BlackHole(Sprite* const sprite, Sprite* const deathSprite) :
		SpaceObject(sprite, BLACK_HOLE_START_POSITION, START_MASS), deathSprite(deathSprite)
	{
		radius = calculateRadius(mass);
		dimensions = { radius * 2, radius * 2 };
	}

	BlackHole::~BlackHole()
	{
		delete deathEffect;
	}

	void BlackHole::setDirection(vec2 direction)
	{
		this->direction = direction;
	}

	void BlackHole::setPhase(BlackHole::Phase phase)
	{
		this->phase = phase;
	}

	void BlackHole::addMass(float mass)
	{
		setMass(this->mass + mass);
	}

	void BlackHole::update(float deltaTime)
	{
		SpaceObject::update(deltaTime);
		if (destroyed) return;

		switch (phase) {
			case ALIVE:
				position += direction * speed * deltaTime;
				position.x = Modulo(position.x, ScreenWidth);
				position.y = Modulo(position.y, ScreenHeight);

				// every second the mass shrinks by the massLossRate times the initial mass
				mass *= powf(1 - massLossRate, deltaTime);
				if (mass < CRITICAL_MASS) phase = CRITICAL;
				break;
			case CRITICAL:
				mass -= CRITICAL_MASS * deltaTime / COLLAPSE_TIME;
				if (mass <= 0)
				{
					mass = 0;
					deathEffect = new ParticleEffect(deathSprite, position);
					phase = IMPLOSION;
				}
				break;
			case IMPLOSION:
				deathEffect->update(deltaTime);
				if (deathEffect->isFinished()) {
					phase = DEATH;
					destroy();
				}
				break;
		}
	} 

	void BlackHole::consumeAsteroid(Asteroid& asteroid)
	{
		asteroid.destroy();
		addMass(asteroid.getMass());
	}

	void BlackHole::draw(Tmpl8::Surface* const screen)
	{
		vec2 topLeftPosition = getTopLeftPosition();
		int curFrame = (int)(animationProgress * sprite->GetNumFrames());
		sprite->SetFrame(curFrame);
		switch (phase)
		{
		case ALIVE:
		case CRITICAL:
			sprite->DrawScaledWrapAround((int)topLeftPosition.x, (int)topLeftPosition.y, (int)dimensions.x, (int)dimensions.y, screen);
			break;
		case IMPLOSION:
			deathEffect->draw(screen);
			break;
		}
	}

	float BlackHole::calculateRadius(float mass)
	{
		return mass * METERS_PER_EARTH_MASS;
	}
}
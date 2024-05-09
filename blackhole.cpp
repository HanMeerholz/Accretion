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
		deathEffect = new ParticleEffect(deathSprite, position);
	}

	BlackHole::~BlackHole()
	{
		delete deathEffect;
	}

	void BlackHole::setDirection(vec2 direction)
	{
		this->direction = direction;
	}

	BlackHole::Phase BlackHole::getPhase()
	{
		return phase;
	}

	void BlackHole::setPhase(BlackHole::Phase phase)
	{
		this->phase = phase;
	}

	void BlackHole::reset()
	{
		position = BLACK_HOLE_START_POSITION;
		setMass(BlackHole::START_MASS);
		phase = BlackHole::ALIVE;
		deathEffect->reset();
		massLossRate = MIN_MASS_LOSS_RATE;
		speed = MIN_SPEED;
		destroyed = false;
	}

	void BlackHole::addMass(float mass)
	{
		setMass(this->mass + mass);
	}

	void BlackHole::update(float deltaTime)
	{
		SpaceObject::update(deltaTime);

		switch (phase) {
			case ALIVE:
				position += direction * speed * deltaTime;

				// this is how the wrap-around is implemented
				position.x = Modulo(position.x, ScreenWidth);
				position.y = Modulo(position.y, ScreenHeight);

				// every second the mass shrinks by the massLossRate times the current mass
				mass *= powf(1 - massLossRate, deltaTime);
				if (mass < CRITICAL_MASS) phase = IMPLODING;

				// speed and mass loss slowly increases over time, making the game more challenging as time progresses
				if (speed <= MAX_SPEED) {
					float acceleration = (MAX_SPEED - MIN_SPEED) / DIFFICULTY_RAMPUP_TIME;
					speed += acceleration * deltaTime;
					if (speed > MAX_SPEED) speed = MAX_SPEED;
				}
				if (massLossRate <= MAX_MASS_LOSS_RATE) {
					float massLossRateIncreasePerSecond = (MAX_MASS_LOSS_RATE - MIN_MASS_LOSS_RATE) / DIFFICULTY_RAMPUP_TIME;
					massLossRate += massLossRateIncreasePerSecond * deltaTime;
					if (massLossRate > MAX_MASS_LOSS_RATE) massLossRate = MAX_MASS_LOSS_RATE;
				}
				break;
			case IMPLODING:
				// make sure the black hole collapses in the collapse time
				mass -= CRITICAL_MASS * deltaTime / COLLAPSE_TIME;
				if (mass <= 0.0f)
				{
					setMass(0.0f);
					deathEffect->setPosition(position);
					destroy();
					phase = EXPLODING;
				}
				break;
			case EXPLODING:
				deathEffect->update(deltaTime);
				if (deathEffect->isFinished())
					phase = EXPLODED;
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
			case IMPLODING:
				// draw wrapped around so it properly handles part of the sprite being over the edge of the screen
				sprite->DrawScaledWrapAround((int)topLeftPosition.x, (int)topLeftPosition.y, (int)dimensions.x, (int)dimensions.y, screen);
				break;
			case EXPLODING:
				deathEffect->draw(screen);
				break;
		}
	}

	float BlackHole::calculateRadius(float mass)
	{
		// black holes have this strange property where their density decreases the larger they get, so their mass and radius are proportional
		return mass * RADIUS_TO_MASS_RATIO;
	}
}
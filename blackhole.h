#pragma once

#include "template.h"
#include "surface.h"
#include "asteroid.h"
#include "particleEffect.h"

namespace Accretion
{

class Asteroid;

static Tmpl8::vec2 const BLACK_HOLE_START_POSITION = { ScreenWidth / 2, ScreenHeight / 2 };

class BlackHole : public SpaceObject
{
public:
	// in earth masses
	static constexpr float MIN_MASS = 100.0f;
	static constexpr float CRITICAL_MASS = 1000.0f;
	static constexpr float START_MASS = 4000.0f;
	static constexpr float MAX_MASS = 25000.0f;

	static constexpr float MIN_MASS_LOSS_RATE = 0.02f;
	static constexpr float MAX_MASS_LOSS_RATE = 0.2f;

	// time in seconds
	static constexpr float TIME_UNTIL_MAX_MASS_LOSS_RATE = 300.0f;
	static constexpr float COLLAPSE_TIME = 1.0f;

	static constexpr float METERS_PER_EARTH_MASS = 0.008868f;

	enum Phase {
		ALIVE, IMPLODING, EXPLODING, EXPLODED
	};

	// structors
	BlackHole() = delete;
	BlackHole(Tmpl8::Sprite* const sprite, Tmpl8::Sprite* const deathSprite);
	~BlackHole();

	// getters/setters
	void setDirection(Tmpl8::vec2 direction);
	Phase getPhase();
	void setPhase(BlackHole::Phase phase);

	void reset();
	
	// physics
	void update(float deltaTime) override;
	void consumeAsteroid(Asteroid& asteroid);

	// sprite
	void draw(Tmpl8::Surface* const screen) override;

private:
	Tmpl8::Sprite* const deathSprite;
	ParticleEffect* deathEffect;

	// pixels per frame
	float const speed = 180.0f;

	Phase phase = ALIVE;

	float massLossRate = MIN_MASS_LOSS_RATE;
	Tmpl8::vec2 direction = { 0.0f, 0.0f };

	void addMass(float mass);
	float calculateRadius(float mass);
};
}
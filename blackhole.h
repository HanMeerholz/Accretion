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

	// time in seconds
	static constexpr float COLLAPSE_TIME = 1.0f;

	static constexpr float METERS_PER_EARTH_MASS = 0.008868f;

	enum Phase {
		ALIVE, CRITICAL, IMPLOSION, DEATH
	};

	// structors
	BlackHole() = delete;
	BlackHole(Tmpl8::Sprite* const sprite, Tmpl8::Sprite* const deathSprite);
	~BlackHole();

	// getters/setters
	void setDirection(Tmpl8::vec2 direction);
	void setPhase(BlackHole::Phase phase);
	
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

	float massLossRate = 0.05f;
	Tmpl8::vec2 direction = { 0.0f, 0.0f };

	void addMass(float mass);
	float calculateRadius(float mass);
};
}
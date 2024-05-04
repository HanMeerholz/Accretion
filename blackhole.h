#pragma once

#include "template.h"
#include "surface.h"
#include "asteroid.h"
#include "spritedgameobject.h"
#include "particleEffect.h"

namespace Accretion
{

class Asteroid;

// in earth masses
static constexpr float BLACK_HOLE_MAX_MASS = 25000.0f;
static constexpr float BLACK_HOLE_START_MASS = 4000.0f;
static constexpr float METERS_PER_EARTH_MASS = 0.008868f;
static Tmpl8::vec2 const BLACK_HOLE_START_POSITION = { ScreenWidth / 2, ScreenHeight / 2 };

class BlackHole : public SpritedGameObject
{
public:
	enum Phase {
		ALIVE, CRITICAL, IMPLOSION, DEATH
	};

	// structors
	BlackHole() = delete;
	BlackHole(Tmpl8::Sprite* const sprite, Tmpl8::Sprite* const deathSprite);

	// getters/setters
	void setDirection(Tmpl8::vec2 direction);
	void setPhase(BlackHole::Phase phase);
	
		// physics
	void update(float deltaTime);
	void consumeAsteroid(Asteroid& asteroid);

	// sprite
	void draw(Tmpl8::Surface* const screen, float currentTime);
	void draw(Tmpl8::Surface* const screen);
private:
	Tmpl8::Sprite* const deathSprite;
	ParticleEffect* deathEffect;
	float deathAnimationTime = 0.0f;

	// pixels per frame
	float const speed = 180.0f;

	Phase phase = ALIVE;

	float const criticalMass = 1000.0f;
	float const minMass = 100.0f;

	float massLossRate = 0.05f;
	Tmpl8::vec2 direction = { 0.0f, 0.0f };

	void addMass(float mass);
	float calculateRadius(float mass);
	Tmpl8::vec2 getLeftTopPosition();
};
}
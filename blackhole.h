#pragma once

#include "template.h"
#include "surface.h"
#include "asteroid.h"
#include "spritedgameobject.h"

namespace Accretion
{

class Asteroid;

static constexpr float BLACK_HOLE_START_MASS = 0.03386f;
static Tmpl8::vec2 const BLACK_HOLE_START_POSITION = { ScreenWidth / 2, ScreenHeight / 2 };

class BlackHole : public SpritedGameObject
{
public:
	// structors
	BlackHole() = delete;
	BlackHole(Tmpl8::Sprite* const sprite);

	// movement
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();

	// physics
	void update();
	void consumeAsteroid(Asteroid& asteroid);

	// sprite
	void draw(Tmpl8::Surface* const screen, float currentTime);
	void draw(Tmpl8::Surface* const screen);
private:
	// pixels per frame
	float const speed = 1.8f;
	float const criticalMass = 0.003f;
	float const metersPerSolarMass = 2953.337;
	float const massLossRate = 0.001f;

	void addMass(float mass);
	float calculateRadius(float mass);
	Tmpl8::vec2 getLeftTopPosition();
};
}
#pragma once

#include "template.h"
#include "surface.h"
#include "asteroid.h"
#include "spritedgameobject.h"

namespace Accretion
{

class Asteroid;

class BlackHole : public SpritedGameObject
{
public:
	// structors
	BlackHole() = delete;
	BlackHole(Tmpl8::Sprite* const sprite);

	// getters/setters
	float getMass();

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
	Tmpl8::vec2 const startPosition = { ScreenWidth / 2, ScreenHeight / 2 };
	
	// in solar masses
	float mass = 0.03386f;

	void addMass(float mass);
	float calculateRadius(float mass);
	Tmpl8::vec2 getLeftTopPosition();
};
}
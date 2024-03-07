#pragma once

#include "template.h"
#include "surface.h"

namespace Accretion
{

class BlackHole
{
public:
	// structors
	BlackHole() = delete;
	BlackHole(Tmpl8::Sprite* const sprite);
	~BlackHole();

	// getters/setters
	Tmpl8::vec2 getPosition();
	void setPosition(Tmpl8::vec2 position);
	bool isDestroyed();
	float getMass();
	float getRadius();

	// movement
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();

	// physics
	void update();

	// sprite
	void draw(Tmpl8::Surface* const screen, float currentTime);
private:
	float const speed = 1.8f;
	float const criticalMass = 0.003f;
	float const metersPerSolarMass = 2953.337;

	Tmpl8::Sprite* const sprite;
	Tmpl8::vec2 position = { 150, 150 };

	bool destroyed = false;
	
	// in solar masses
	float mass = 0.03386f;
	// in meters
	float radius;

	// animation speed in frames per second
	float const animationSpeed = 10.0f;
	float const animationLength;

	Tmpl8::vec2 getLeftTopPosition();
	void draw(Tmpl8::Surface* const screen);
	float calculateRadius(float mass);
};
}
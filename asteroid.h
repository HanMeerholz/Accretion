#pragma once
#include "template.h"
#include "surface.h"
#include "spaceObject.h"
#include "blackHole.h"

namespace Accretion
{
class BlackHole;

// gravitational constant in newton m^2 / (earth mass)^2
static constexpr float GRAVITATIONAL_CONSTANT = 200.0f;
static constexpr float ASTEROID_SPRITE_RADIUS_FACTOR = 1.13f;

class Asteroid : public SpaceObject
{
public:
	// structors
	Asteroid(Tmpl8::Sprite* const sprite, Tmpl8::vec2 position, float mass, Tmpl8::vec2 velocity);

	// physics
	void update(BlackHole& blackHole, float deltaTime);
	void update(float deltaTime) override;

	// sprite
	void draw(Tmpl8::Surface* const screen) override;
private:
	// solar masses per m^3
	float const density = .003;

	Tmpl8::vec2 velocity;

	float calculateRadius(float mass);
};
}
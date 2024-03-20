#pragma once
#include "template.h"
#include "surface.h"
#include "spritedgameobject.h"
#include "blackhole.h"

namespace Accretion
{
	class BlackHole;

	// gravitational constant in newton m^2 / (solar mass)^2
	static constexpr float GRAVITATIONAL_CONSTANT = 0.02;
	static constexpr float ASTEROID_SPRITE_RADIUS_FACTOR = 1.13f;

	class Asteroid : public SpritedGameObject
	{
	public:
		// structors
		Asteroid(Tmpl8::Sprite* const sprite, Tmpl8::vec2 position, float mass);
		Asteroid(Tmpl8::Sprite* const sprite, Tmpl8::vec2 position, float mass, Tmpl8::vec2 velocity);

		// sprite
		void draw(Tmpl8::Surface* const screen, float currentTime);
		void draw(Tmpl8::Surface* const screen);
		void update(BlackHole& blackHole);
	private:
		// solar masses per m^3
		float const density = .003;

		Tmpl8::vec2 velocity;
		bool destroyed = false;

		float calculateRadius(float mass);
		Tmpl8::vec2 getLeftTopPosition();
	};
}
#pragma once
#include "template.h"
#include "surface.h"
#include "spritedgameobject.h"
#include "blackhole.h"

namespace Accretion
{
	class BlackHole;

	class Asteroid : public SpritedGameObject
	{
	public:
		// structors
		Asteroid(Tmpl8::Sprite* const sprite);
		Asteroid(Tmpl8::Sprite* const sprite, Tmpl8::vec2 position, float radius);
		Asteroid(Tmpl8::Sprite* const sprite, Tmpl8::vec2 position, float radius, Tmpl8::vec2 velocity);

		// sprite
		void draw(Tmpl8::Surface* const screen, float currentTime);
		void draw(Tmpl8::Surface* const screen);
		void update(BlackHole& blackHole);
	private:
		// gravitational constant in newton m^2 / (solar mass)^2
		float const gravity = 10000;
		// solar masses per m^3
		float density = 1000.0f;

		Tmpl8::vec2 velocity = { 0.0f, 0.0f };
		bool destroyed = false;

		float calculateRadius(float mass);
		Tmpl8::vec2 getLeftTopPosition();
	};
}
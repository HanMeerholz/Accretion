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
		Asteroid(Tmpl8::Sprite* const sprite, Tmpl8::vec2 position, float mass);
		Asteroid(Tmpl8::Sprite* const sprite, Tmpl8::vec2 position, float mass, Tmpl8::vec2 velocity);

		// sprite
		void draw(Tmpl8::Surface* const screen, float currentTime);
		void draw(Tmpl8::Surface* const screen);
		void update(BlackHole& blackHole);
	private:
		// gravitational constant in newton m^2 / (solar mass)^2
		float const gravity = 10000;
		// solar masses per m^3
		float const density = .00000001;

		Tmpl8::vec2 velocity;
		bool destroyed = false;

		float calculateRadius(float mass);
		Tmpl8::vec2 getLeftTopPosition();
	};
}
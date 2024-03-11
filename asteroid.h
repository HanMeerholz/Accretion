#pragma once
#include "template.h"
#include "surface.h"
#include "gameobject.h"
#include "blackhole.h"

namespace Accretion
{
	class BlackHole;

	class Asteroid : public GameObject
	{
	public:
		// structors
		Asteroid();
		Asteroid(Tmpl8::vec2 position, float radius);
		Asteroid(Tmpl8::vec2 position, float radius, Tmpl8::vec2 velocity);

		// sprite
		void draw(Tmpl8::Surface* const screen);
		void update(BlackHole& blackHole);
	private:
		// gravitational constant in newton m^2 / (solar mass)^2
		float const gravity = 20000;
		// solar masses per m^3
		float density = 1000.0f;

		Tmpl8::vec2 velocity = { 0.0f, 0.0f };
		bool destroyed = false;

		float calculateRadius(float mass);
	};
}
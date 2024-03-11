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
		Tmpl8::vec2 velocity = { 0.0f, 0.0f };
		bool destroyed = false;
	};
}
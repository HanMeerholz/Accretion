#pragma once
#include "template.h"
#include "surface.h"

namespace Accretion
{

	class Asteroid
	{
	public:
		// structors
		Asteroid();
		Asteroid(Tmpl8::vec2 position, float radius);

		// getters/setters
		Tmpl8::vec2 getPosition();
		void setPosition(Tmpl8::vec2 position);
		bool isDestroyed();
		void setDestroyed();
		float getRadius();

		// sprite
		void draw(Tmpl8::Surface* const screen);
	private:
		Tmpl8::vec2 position = { 0.0f, 0.0f };

		bool destroyed = false;
		float radius = 0.0f;
	};
}
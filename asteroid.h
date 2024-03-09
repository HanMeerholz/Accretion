#pragma once
#include "template.h"
#include "surface.h"
#include "gameobject.h"

namespace Accretion
{

	class Asteroid : public GameObject
	{
	public:
		// structors
		Asteroid();
		Asteroid(Tmpl8::vec2 position, float radius);

		// sprite
		void draw(Tmpl8::Surface* const screen);
	private:
		bool destroyed = false;
	};
}
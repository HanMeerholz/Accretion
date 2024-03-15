#pragma once

#include "template.h"
#include "surface.h"

namespace Accretion
{
class GameObject {
public:
	// constructors
	GameObject();
	GameObject(Tmpl8::vec2 position);
	GameObject(Tmpl8::vec2 position, float radius);

	// getters/setters
	Tmpl8::vec2 getPosition();
	void setPosition(Tmpl8::vec2 position);
	bool isDestroyed();
	void setDestroyed();
	float getRadius();
	void setRadius(float radius);

	// collision
	bool isConsumedBy(GameObject& gameObject);
	float distance(GameObject& gameObject);

	// draw
	virtual void draw(Tmpl8::Surface* const screen) = 0;
private:
	float radius;
	bool destroyed = false;
	Tmpl8::vec2 position = { 150, 150 };

	virtual float calculateRadius(float mass) = 0;
};
}
#pragma once

#include "template.h"

namespace Accretion
{
class GameObject {
public:
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
private:
	float radius;
	bool destroyed = false;
	Tmpl8::vec2 position = { 150, 150 };

	virtual float calculateRadius(float mass) = 0;
};
}
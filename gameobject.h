#pragma once

#include "template.h"
#include "surface.h"

namespace Accretion
{
class GameObject {
public:
	// constructors
	GameObject() = delete;
	GameObject(Tmpl8::vec2 position);
	GameObject(Tmpl8::vec2 position, float mass);

	// getters/setters
	Tmpl8::vec2 getPosition();
	void setPosition(Tmpl8::vec2 position);
	float getMass();
	bool isDestroyed();
	void setDestroyed();
	float getRadius();

	// physics
	virtual void update(float deltaTime);

	// collision
	bool isConsumedBy(GameObject& gameObject);
	float distance(GameObject& gameObject);

	// draw
	virtual void draw(Tmpl8::Surface* const screen) = 0;

protected:
	// in solar masses
	float mass;
	// in meters
	float radius;
	bool destroyed = false;
	Tmpl8::vec2 position = { 150, 150 };

private:
	virtual float calculateRadius(float mass) = 0;
};
}
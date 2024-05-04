#pragma once

#include "gameObject.h"

namespace Accretion
{
class SpaceObject: public GameObject
{
public:
	// constructors
	SpaceObject() = delete;
	SpaceObject(Tmpl8::Sprite *sprite, Tmpl8::vec2 position, float mass);

	// getters/setters
	float getMass();
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

private:
	virtual float calculateRadius(float mass) = 0;
};
}
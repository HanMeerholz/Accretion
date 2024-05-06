#pragma once

#include "gameObject.h"

namespace Accretion
{
class SpaceObject: public GameObject
{
public:
	// constructors
	SpaceObject() = delete;
	SpaceObject(Tmpl8::Sprite* const sprite, Tmpl8::vec2 position, float mass);
	SpaceObject(Tmpl8::Sprite* const sprite, Tmpl8::vec2 position, float animationSpeed, int initialFrame, bool drawReverse, float mass);

	// physics
	virtual void update(float deltaTime);

	// getters/setters
	float getMass();
	void setMass(float mass);
	float getRadius();

	// collision
	bool isConsumedBy(SpaceObject& object);
	float distanceTo(SpaceObject& object);

protected:
	// in solar masses
	float mass;
	// in meters
	float radius;

	void setRadius(float radius);

private:
	virtual float calculateRadius(float mass) = 0;
};
}
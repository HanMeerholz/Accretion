#include "spaceObject.h"
using namespace Tmpl8;

namespace Accretion
{
SpaceObject::SpaceObject(Sprite* sprite, Tmpl8::vec2 position, float mass)
	: GameObject(sprite, position, vec2{0, 0}), mass(mass), radius(0.0f)
{
}

SpaceObject::SpaceObject(Tmpl8::Sprite* const sprite, Tmpl8::vec2 position, float animationSpeed, int initialFrame, bool drawReverse, float mass)
	: GameObject(sprite, position, vec2{0, 0}, animationSpeed, initialFrame, drawReverse), mass(mass), radius(0.0f)
{
}

float SpaceObject::getMass()
{
	return mass;
}

float SpaceObject::getRadius()
{
	return radius;
}

void SpaceObject::update(float deltaTime)
{
	GameObject::update(deltaTime);
	setMass(mass);
}

bool SpaceObject::isConsumedBy(SpaceObject& object)
{
	return distanceTo(object) + radius < object.radius;
}

float SpaceObject::distanceTo(SpaceObject& object)
{
	return (position - object.position).length();
}


void SpaceObject::setRadius(float radius)
{
	this->radius = radius;
	setDimensions({ radius * 2, radius * 2 });
}

void SpaceObject::setMass(float mass)
{
	this->mass = mass;
	setRadius(calculateRadius(mass));
}

}

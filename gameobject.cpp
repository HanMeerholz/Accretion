#include "gameobject.h"

using namespace Tmpl8;

namespace Accretion {
GameObject::GameObject(vec2 position)
	: GameObject(position, 0.0f)
{}

GameObject::GameObject(vec2 position, float mass)
	: position(position), mass(mass)
{ }

vec2 GameObject::getPosition()
{
	return position;
}

void GameObject::setPosition(vec2 position)
{
	this->position = position;
}

float GameObject::getMass()
{
	return mass;
}

bool GameObject::isDestroyed()
{
	return destroyed;
}

void GameObject::setDestroyed()
{
	destroyed = true;
}

float GameObject::getRadius()
{
	return radius;
}

void GameObject::update(float deltaTime)
{
	radius = calculateRadius(mass);
}

bool GameObject::isConsumedBy(GameObject& gameObject)
{
	return distance(gameObject) + radius < gameObject.radius;
}

float GameObject::distance(GameObject& gameObject)
{
	return (position - gameObject.position).length();
}
}
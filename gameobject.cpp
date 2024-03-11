#include "gameobject.h"

using namespace Tmpl8;

namespace Accretion {
GameObject::GameObject()
	: GameObject({ 0.0f, 0.0f }, 0.0f)
{}

GameObject::GameObject(vec2 position)
	: GameObject(position, 0.0f)
{}

GameObject::GameObject(vec2 position, float radius)
	: position(position), radius(radius)
{}

vec2 GameObject::getPosition()
{
	return position;
}

void GameObject::setPosition(vec2 position)
{
	this->position = position;
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

void GameObject::setRadius(float radius)
{
	this->radius = radius;
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
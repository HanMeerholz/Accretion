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
	float distance = sqrt(pow(position.x - gameObject.position.x, 2) + pow(position.y - gameObject.position.y, 2));
	return distance + radius < gameObject.radius;
}
}
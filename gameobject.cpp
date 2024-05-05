#include "gameobject.h"

using namespace Tmpl8;

namespace Accretion {
GameObject::GameObject(Tmpl8::Sprite* sprite, Tmpl8::vec2 position)
	: GameObject(sprite, position, vec2{(float)sprite->GetWidth(), (float)sprite->GetHeight()})
{ }

GameObject::GameObject(Tmpl8::Sprite* sprite, Tmpl8::vec2 position, Tmpl8::vec2 dimensions)
	: GameObject(sprite, position, dimensions, 10.0f, 0, false)
{ }

GameObject::GameObject(Tmpl8::Sprite* sprite, Tmpl8::vec2 position, Tmpl8::vec2 dimensions, float animationSpeed, int initialFrame, bool drawReverse)
	: sprite(sprite), position(position), dimensions(dimensions), animationSpeed(animationSpeed), animationProgress((float) initialFrame / (float) sprite->GetNumFrames()), drawReverse(drawReverse)
{ }

vec2 GameObject::getPosition()
{
	return position;
}

void GameObject::setPosition(vec2 position)
{
	this->position = position;
}

void GameObject::setDimensions(Tmpl8::vec2 dimensions)
{
	this->dimensions = dimensions;
}

bool GameObject::isDestroyed()
{
	return destroyed;
}

void GameObject::destroy()
{
	destroyed = true;
}

void GameObject::update(float deltaTime)
{
	float animationLength = sprite->GetNumFrames() / animationSpeed;
	float currentAnimationTime = animationProgress * animationLength;
	currentAnimationTime = Modulo(drawReverse ? currentAnimationTime - deltaTime : currentAnimationTime + deltaTime, animationLength);
	animationProgress = currentAnimationTime / animationLength;
}

void GameObject::draw(Tmpl8::Surface* const screen)
{
	vec2 topLeftPosition = getTopLeftPosition();

	int curFrame = (int)(animationProgress * sprite->GetNumFrames());
	sprite->SetFrame(curFrame);

	sprite->Draw(screen, (int) topLeftPosition.x, (int) topLeftPosition.y);
}

vec2 GameObject::getTopLeftPosition()
{
	return position - vec2{ dimensions.x / 2, dimensions.y / 2 };
}
}
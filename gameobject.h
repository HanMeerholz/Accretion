#pragma once

#include "template.h"
#include "surface.h"

namespace Accretion
{
class GameObject {
public:
	// constructors
	GameObject() = delete;
	GameObject(Tmpl8::Sprite* const sprite, Tmpl8::vec2 position);
	GameObject(Tmpl8::Sprite* const sprite, Tmpl8::vec2 position, Tmpl8::vec2 dimensions);
	GameObject(Tmpl8::Sprite* const sprite, Tmpl8::vec2 position, Tmpl8::vec2 dimensions, float animationSpeed, int initialFrame, bool drawReverse);

	// getters/setters
	Tmpl8::vec2 getPosition();
	void setPosition(Tmpl8::vec2 position);
	void setDimensions(Tmpl8::vec2 dimensions);
	bool isDestroyed();
	void destroy();

	// physics
	virtual void update(float deltaTime);

	// draw
	virtual void draw(Tmpl8::Surface* const screen);

protected:
	Tmpl8::Sprite* const sprite;

	bool destroyed = false;
	Tmpl8::vec2 position;
	Tmpl8::vec2 dimensions;

	// animation speed in frames per second
	float animationSpeed;
	float animationProgress;
	bool drawReverse;

	Tmpl8::vec2 getTopLeftPosition();
};
}
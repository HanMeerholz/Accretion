#pragma once
#include "template.h"
#include "surface.h"
#include "gameobject.h"

namespace Accretion
{
class SpritedGameObject : public GameObject {
public:
	// structors
	SpritedGameObject() = delete;
	SpritedGameObject(Tmpl8::Sprite* const sprite, Tmpl8::vec2 position);
	SpritedGameObject(Tmpl8::Sprite* const sprite, Tmpl8::vec2 position, float mass);

	// sprite
	void draw(Tmpl8::Surface* const screen, float currentTime);
	virtual void draw(Tmpl8::Surface* const screen) = 0;

protected:
	Tmpl8::Sprite* const sprite;
	int animationOffset = 0;
	bool drawReverse = false;
	// animation speed in frames per second
	float animationSpeed = 10.0f;

private:
	virtual Tmpl8::vec2 getLeftTopPosition() = 0;
};
}
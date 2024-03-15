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
	SpritedGameObject(Tmpl8::Sprite* const sprite);
	SpritedGameObject(Tmpl8::Sprite* const sprite, Tmpl8::vec2 position, float radius);
	~SpritedGameObject();

	// sprite
	void draw(Tmpl8::Surface* const screen, float currentTime);
	virtual void draw(Tmpl8::Surface* const screen) = 0;

protected:
	Tmpl8::Sprite* const sprite;

private:
	// animation speed in frames per second
	float const animationSpeed = 10.0f;
	float const animationLength = sprite->GetNumFrames() / animationSpeed;
};
}
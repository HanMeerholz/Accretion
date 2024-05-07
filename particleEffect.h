#pragma once

#include "template.h"
#include "surface.h"
#include "gameObject.h"

namespace Accretion
{
class ParticleEffect : public GameObject
{
public:
	// structors
	ParticleEffect() = delete;
	ParticleEffect(Tmpl8::Sprite* const sprite, Tmpl8::vec2 position);

	virtual void update(float deltaTime);
	void reset();

	bool isFinished();

	// sprite
	void draw(Tmpl8::Surface* const screen);
private:
	bool finished = false;
};
}
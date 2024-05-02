#pragma once

#include "spritedgameobject.h"

namespace Accretion
{
class ParticleEffect
{
public:
	// structors
	ParticleEffect() = delete;
	ParticleEffect(Tmpl8::Sprite* const sprite, Tmpl8::vec2 position);

	float getStartTime();
	void setStartTime(float startTime);
	bool isFinished();


	// sprite
	void draw(Tmpl8::Surface* const screen, float currentTime);
	void draw(Tmpl8::Surface* const screen);
private:
	// animation speed in frames per second
	float startTime = 0.0f;
	float const animationSpeed = 60.0f;
	Tmpl8::Sprite* const sprite;

	Tmpl8::vec2 const position;
	Tmpl8::intvec2 const dimensions;
	bool finished = false;
};
}
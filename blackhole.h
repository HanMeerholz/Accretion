#pragma once

#include "template.h"

namespace Accretion
{
class Sprite;

class BlackHole
{
public:
	BlackHole();
	Tmpl8::vec2 getPosition();
	void setPosition(Tmpl8::vec2 position);

	void draw(float currentTime);
private:
	Tmpl8::Sprite* sprite;
	int const blackHoleNrFrames = 30;
	float const blackHoleSpeed = 0.8f;

	Tmpl8::vec2 position = { 100, 100 };

	// animation speed in frames per second
	float const animationSpeed = 10.0f;
	float const animationLength = blackHoleNrFrames / animationSpeed;
};
}
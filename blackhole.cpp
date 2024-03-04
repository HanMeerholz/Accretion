#include "blackhole.h"
#include "surface.h"

namespace Accretion
{
BlackHole::BlackHole()
{
	sprite = new Tmpl8::Sprite(new Tmpl8::Surface("assets/blackhole.png"), blackHoleNrFrames);
}

Tmpl8::vec2 BlackHole::getPosition()
{
	return position;
}

void BlackHole::setPosition(Tmpl8::vec2 position)
{
	this->position = position;
}

void BlackHole::draw()
}
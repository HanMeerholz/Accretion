#include "blackhole.h"
#include "surface.h"

using namespace Tmpl8;

namespace Accretion
{
	BlackHole::BlackHole(Sprite* const sprite) :
		sprite(sprite),
		animationLength(sprite->GetNumFrames() / animationSpeed)
	{
		radius = calculateRadius(mass);
	}

	BlackHole::~BlackHole()
	{
		delete sprite;
	}

	vec2 BlackHole::getPosition()
	{
		return position;
	}

	void BlackHole::setPosition(vec2 position)
	{
		this->position = position;
	}

	bool BlackHole::isDestroyed()
	{
		return destroyed;
	}

	void BlackHole::moveUp()
	{
		this->position.y -= speed;
	}

	void BlackHole::moveDown()
	{
		this->position.y += speed;
	}

	void BlackHole::moveLeft()
	{
		this->position.x -= speed;
	}

	void BlackHole::moveRight()
	{
		this->position.x += speed;
	}

	void BlackHole::update()
	{
		mass *= 0.999f;
		if (mass < criticalMass) destroyed = true;
		radius = calculateRadius(mass);
	}

	void BlackHole::draw(Tmpl8::Surface* const screen, float const currentTime)
	{
		int curFrame = (float)(fmod(currentTime, animationLength) / animationLength) * sprite->GetNumFrames();
		sprite->SetFrame(curFrame);
		drawScaled(screen);
	}

	float BlackHole::calculateRadius(float mass)
	{
		return mass * BlackHole::metersPerSolarMass;
	}

	vec2 BlackHole::getLeftTopPosition()
	{
		return { position.x - radius , position.y - radius };
	}

	void BlackHole::drawScaled(Tmpl8::Surface* screen)
	{
		vec2 leftTopPosition = getLeftTopPosition();
		sprite->DrawScaled(leftTopPosition.x, leftTopPosition.y, 2 * radius, 2 * radius, screen);
	}
}
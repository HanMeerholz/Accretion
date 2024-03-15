#include "spritedgameobject.h"

namespace Accretion {
	SpritedGameObject::SpritedGameObject(Tmpl8::Sprite* const sprite) :
		sprite(sprite)
	{ }

	SpritedGameObject::SpritedGameObject(Tmpl8::Sprite* const sprite, Tmpl8::vec2 position, float radius) :
		GameObject(position, radius), sprite(sprite)
	{
	}

	SpritedGameObject::~SpritedGameObject()
	{
		delete sprite;
	}

	void SpritedGameObject::draw(Tmpl8::Surface* const screen, float currentTime)
	{
		int curFrame = (float)(fmod(currentTime, animationLength) / animationLength) * sprite->GetNumFrames();
		sprite->SetFrame(curFrame);
		draw(screen);
	}
}

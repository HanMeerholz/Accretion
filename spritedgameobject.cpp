#include "spritedgameobject.h"

namespace Accretion {
	SpritedGameObject::SpritedGameObject(Tmpl8::Sprite* const sprite, Tmpl8::vec2 position) :
		GameObject(position), sprite(sprite)
	{ }

	SpritedGameObject::SpritedGameObject(Tmpl8::Sprite* const sprite, Tmpl8::vec2 position, float mass) :
		GameObject(position, mass), sprite(sprite)
	{ }

	SpritedGameObject::~SpritedGameObject()
	{
		delete sprite;
	}

	void SpritedGameObject::draw(Tmpl8::Surface* const screen, float currentTime)
	{
		int curFrame = (int) ((float)(fmod(currentTime, animationLength) / animationLength) * sprite->GetNumFrames());
		sprite->SetFrame(curFrame);
		draw(screen);
	}
}

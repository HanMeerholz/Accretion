#include "spritedgameobject.h"

namespace Accretion {
	SpritedGameObject::SpritedGameObject(Tmpl8::Sprite* const sprite, Tmpl8::vec2 position) :
		GameObject(position), sprite(sprite)
	{ }

	SpritedGameObject::SpritedGameObject(Tmpl8::Sprite* const sprite, Tmpl8::vec2 position, float mass) :
		GameObject(position, mass), sprite(sprite)
	{ }

	void SpritedGameObject::draw(Tmpl8::Surface* const screen, float currentTime)
	{
		float const animationLength = sprite->GetNumFrames() / animationSpeed;
		int numFrames = sprite->GetNumFrames();
		int curFrame = (int) ((float)(fmod(currentTime, animationLength) / animationLength) * numFrames);

		curFrame = (curFrame + animationOffset) % numFrames;
		if (drawReverse) curFrame = numFrames - curFrame - 1;

		sprite->SetFrame(curFrame);
		draw(screen);
	}
}

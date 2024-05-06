#include "particleEffect.h"

using namespace Tmpl8;

namespace Accretion
{
ParticleEffect::ParticleEffect(Sprite* const sprite, vec2 position)
	: GameObject(sprite, position, {(float)sprite->GetWidth(), (float)sprite->GetHeight()}, 60.0f, 0, false)
{ }

void ParticleEffect::update(float deltaTime)
{
	if (finished) return;

	float animationLength = sprite->GetNumFrames() / animationSpeed;
	float currentAnimationTime = animationProgress * animationLength;

	GameObject::update(deltaTime);

	if (currentAnimationTime + deltaTime > animationLength)
		finished = true;
}

bool ParticleEffect::isFinished()
{
	return finished;
}

void ParticleEffect::draw(Surface* const screen)
{
	GameObject::draw(screen);
}
}
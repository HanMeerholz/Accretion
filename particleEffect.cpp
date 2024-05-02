#include "particleEffect.h"

using namespace Tmpl8;

namespace Accretion
{
	ParticleEffect::ParticleEffect(Sprite* const sprite, vec2 position)
		: sprite(sprite), position(position), dimensions{ sprite->GetWidth(), sprite->GetHeight() }
{ }

	float ParticleEffect::getStartTime()
	{
		return startTime;
	}

	void ParticleEffect::setStartTime(float startTime)
	{
		this->startTime = startTime;
	}

	bool ParticleEffect::isFinished()
{
	return finished;
}

void ParticleEffect::draw(Surface* const screen, float currentTime)
{
	float const animationTime = currentTime - startTime;
	float const animationLength = sprite->GetNumFrames() / animationSpeed;
	if (animationTime > animationLength) finished = true;
	else {
		int numFrames = sprite->GetNumFrames();
		int curFrame = (int)((float) (animationTime / animationLength) * numFrames);

		sprite->SetFrame(curFrame % numFrames);
		draw(screen);
	}
}

void ParticleEffect::draw(Surface* const screen)
{
	vec2 topLeftPosition = position - vec2{(float) dimensions.x / 2, (float) dimensions.y / 2};
	sprite->Draw(screen, topLeftPosition.x, topLeftPosition.y);
}
}
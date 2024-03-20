#include "progressBar.h"

using namespace Tmpl8;

namespace Accretion {

ProgressBar::ProgressBar(Surface* frame, Surface* leftEdge, Surface* mainBar, Surface* rightEdge, int padding)
	:
	frame(frame), leftEdge(leftEdge), mainBar(mainBar), rightEdge(rightEdge), dimensions({ frame->GetWidth(), frame->GetHeight() }), padding(padding)
{}

ProgressBar::~ProgressBar()
{
	delete frame;
	delete leftEdge;
	delete mainBar;
	delete rightEdge;
}

intvec2 ProgressBar::getDimensions()
{
	return dimensions;
}

void ProgressBar::draw(Surface* screen, intvec2 position, float progress)
{
	if (progress > 1.0f) progress = 1.0f;
	frame->CopyTo(screen, position.x, position.y);
	leftEdge->CopyTo(   screen, position.x + relativeLeftEdgePosition.x, position.y + relativeLeftEdgePosition.y);
	mainBar->DrawScaled(screen, position.x + relativeMainBarPosition.x,  position.y + relativeMainBarPosition.y , mainBar->GetWidth() * progress, mainBar->GetHeight());
	intvec2 relativeRightEdgePosition = { relativeMainBarPosition.x + (int) (mainBar->GetWidth() * progress), relativeMainBarPosition.y };
	rightEdge->CopyTo(screen, position.x + relativeRightEdgePosition.x, position.y + relativeRightEdgePosition.y);
}
}

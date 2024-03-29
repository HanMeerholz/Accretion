#include "progressBar.h"

using namespace Tmpl8;

namespace Accretion {

ProgressBar::ProgressBar(Surface* frame, Surface* leftEdge, Surface* mainBar, Surface* rightEdge, int padding)
	:
	frame(frame), leftEdge(leftEdge), mainBar(mainBar), rightEdge(rightEdge), padding(padding)
{
	dimensions = { frame->GetWidth(), frame->GetHeight() };
}

ProgressBar::~ProgressBar()
{
	delete frame;
	delete leftEdge;
	delete mainBar;
	delete rightEdge;
}

void ProgressBar::setProgress(float progress)
{
	if (progress > 1.0f) progress = 1.0f;
	if (progress < 0.0f) progress = 0.0f;
	this->progress = progress;
}

void ProgressBar::draw(Surface* screen)
{
	intvec2 topLeftPosition = getTopLeftPosition();
	frame->CopyTo(screen, topLeftPosition.x, topLeftPosition.y);
	leftEdge->CopyTo(screen, topLeftPosition.x + relativeLeftEdgePosition.x, topLeftPosition.y + relativeLeftEdgePosition.y);
	mainBar->DrawScaled(screen, topLeftPosition.x + relativeMainBarPosition.x, topLeftPosition.y + relativeMainBarPosition.y , mainBar->GetWidth() * progress, mainBar->GetHeight());
	intvec2 relativeRightEdgePosition = { relativeMainBarPosition.x + (int) (mainBar->GetWidth() * progress), relativeMainBarPosition.y };
	rightEdge->CopyTo(screen, topLeftPosition.x + relativeRightEdgePosition.x, topLeftPosition.y + relativeRightEdgePosition.y);
}
}

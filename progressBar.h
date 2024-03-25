#pragma once

#include "template.h"
#include "surface.h"
#include "uiElement.h"

namespace Accretion {

class ProgressBar : public UIElement {
public:
	ProgressBar(Tmpl8::Surface* frame, Tmpl8::Surface* leftEdge, Tmpl8::Surface* mainBar, Tmpl8::Surface* rightEdge, int padding);
	~ProgressBar();
	void setProgress(float progress);

	void draw(Tmpl8::Surface* screen);

private:
	Tmpl8::Surface* const frame;
	Tmpl8::Surface* const leftEdge;
	Tmpl8::Surface* const mainBar;
	Tmpl8::Surface* const rightEdge;

	int const padding;
	float progress = 0.0f;

	Tmpl8::intvec2 relativeLeftEdgePosition = { padding, padding };
	Tmpl8::intvec2 relativeMainBarPosition = { padding + leftEdge->GetWidth(), padding };
};
}
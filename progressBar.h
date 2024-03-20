#pragma once

#include "surface.h"
#include "template.h"

namespace Accretion {

class ProgressBar {
public:
	ProgressBar(Tmpl8::Surface* frame, Tmpl8::Surface* leftEdge, Tmpl8::Surface* mainBar, Tmpl8::Surface* rightEdge, int padding);
	~ProgressBar();

	Tmpl8::intvec2 getDimensions();

	void draw(Tmpl8::Surface* screen, Tmpl8::intvec2 position, float progress);

private:
	Tmpl8::Surface* const frame;
	Tmpl8::Surface* const leftEdge;
	Tmpl8::Surface* const mainBar;
	Tmpl8::Surface* const rightEdge;

	Tmpl8::intvec2 const dimensions;
	int const padding;


	Tmpl8::intvec2 relativeLeftEdgePosition = { padding, padding };
	Tmpl8::intvec2 relativeMainBarPosition = { padding + leftEdge->GetWidth(), padding };
};
}
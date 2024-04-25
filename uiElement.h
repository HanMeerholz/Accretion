#pragma once

#include "template.h"
#include "surface.h"

namespace Accretion {

class UIElement {
public:
	UIElement() = delete;
	UIElement(Tmpl8::intvec2 dimensions);
	UIElement(Tmpl8::intvec2 dimensions, Tmpl8::intvec2 position);

	Tmpl8::intvec2 getDimensions();
	int getWidth();
	int getHeight();
	void setPosition(Tmpl8::intvec2 position);

	virtual void draw(Tmpl8::Surface* screen) = 0;
protected:
	Tmpl8::intvec2 dimensions;
	Tmpl8::intvec2 position;

	Tmpl8::intvec2 getTopLeftPosition();
};
}
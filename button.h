#pragma once

#include "template.h"
#include "surface.h"
#include "uiElement.h"

namespace Accretion
{

class Button : public UIElement
{
public:
	Button(Tmpl8::Surface* buttonUnpressed, Tmpl8::Surface* buttonHover, Tmpl8::Surface* buttonPressed);
	~Button();

	void draw(Tmpl8::Surface* screen);
	void update(Tmpl8::intvec2 mousePos, bool mousePressed);
	bool isPressed();

private:
	Tmpl8::Surface* buttonUnpressed;
	Tmpl8::Surface* buttonHover;
	Tmpl8::Surface* buttonPressed;

	Tmpl8::Surface* currentImage;
};
}
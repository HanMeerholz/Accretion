#pragma once

#include <functional>
#include "template.h"
#include "surface.h"
#include "uiElement.h"

namespace Accretion
{

class Button : public UIElement
{
public:
	Button(Tmpl8::Surface* buttonUnpressed, Tmpl8::Surface* buttonHover, Tmpl8::Surface* buttonPressed, std::function<void()> onPress);
	~Button();

	void draw(Tmpl8::Surface* screen);
	void update(Tmpl8::intvec2 mousePos, bool mousePressed);

private:
	enum ButtonState {
		UNPRESSED, HOVER, PRESSING, PRESSED
	};

	ButtonState buttonState = UNPRESSED;
	std::function<void()> onPress;

	Tmpl8::Surface* buttonUnpressed;
	Tmpl8::Surface* buttonHover;
	Tmpl8::Surface* buttonPressed;

	Tmpl8::Surface* currentImage;

	void updateImage();
};
}
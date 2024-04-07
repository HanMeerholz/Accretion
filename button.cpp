#include "button.h"
#include "surface.h"
#include <iostream>

using namespace Tmpl8;

namespace Accretion
{
	Button::Button(Surface* buttonUnpressed, Surface* buttonHover, Surface* buttonPressed) :
		UIElement({buttonUnpressed->GetWidth(), buttonUnpressed->GetHeight()}),
		buttonUnpressed(buttonUnpressed),
		buttonHover(buttonHover),
		buttonPressed(buttonPressed)
	{ }

	Button::~Button()
	{
		delete buttonUnpressed;
		delete buttonHover;
		delete buttonPressed;
	}

	void Button::draw(Tmpl8::Surface* screen)
	{
		intvec2 topLeftPosition = getTopLeftPosition();
		buttonUnpressed->CopyTo(screen, topLeftPosition.x, topLeftPosition.y);
	}

}
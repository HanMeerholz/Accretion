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
		buttonPressed(buttonPressed),
		currentImage(buttonUnpressed)
	{ }

	Button::~Button()
	{
		delete buttonUnpressed;
		delete buttonHover;
		delete buttonPressed;
	}

	void Button::draw(Surface* screen)
	{
		intvec2 topLeftPosition = getTopLeftPosition();
		currentImage->CopyTo(screen, topLeftPosition.x, topLeftPosition.y);
	}

	void Button::update(intvec2 mousePos, bool mousePressed)
	{
		intvec2 topLeftPosition = getTopLeftPosition();
		intvec2 bottomRightPosition = topLeftPosition + getDimensions() - intvec2{1, 1};

		bool mouseIsInButton = mousePos.x >= topLeftPosition.x && mousePos.x <= bottomRightPosition.x
			&& mousePos.y >= topLeftPosition.y && mousePos.y <= bottomRightPosition.y;

		currentImage = mouseIsInButton ? (mousePressed ? buttonPressed : buttonHover) : buttonUnpressed;
	}

	bool Button::isPressed()
	{
		return currentImage == buttonPressed;
	}

}
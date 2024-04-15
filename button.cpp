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

		ButtonState newButtonState = UNPRESSED;

		switch (buttonState)
		{
		case UNPRESSED:
			if (mouseIsInButton) newButtonState = HOVER;
			break;
		case HOVER:
			if (mouseIsInButton && mousePressed) newButtonState = PRESSING;
			else if (!mouseIsInButton) newButtonState = UNPRESSED;
			break;
		case PRESSING:
			if (!mousePressed) newButtonState = PRESSED;
			break;
		}

		if (buttonState != newButtonState)
		{
			buttonState = newButtonState;
			updateImage();
		}

		std::cout << buttonState << std::endl;
	}

	void Button::updateImage()
	{
		switch (buttonState)
		{
		case UNPRESSED:
		case PRESSED:
			currentImage = buttonUnpressed;
			break;
		case HOVER:
			currentImage = buttonHover;
			break;
		case PRESSING:
			currentImage = buttonPressed;
			break;
		}
	}

	bool Button::isPressed()
	{
		return buttonState == PRESSED;
	}

}
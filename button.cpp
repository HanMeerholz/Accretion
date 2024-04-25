#include "button.h"
#include "surface.h"
#include <iostream>
#include <functional>

using namespace Tmpl8;
using namespace std;

namespace Accretion
{
	Button::Button(Surface* buttonUnpressed, Surface* buttonHover, Surface* buttonPressed, function<void()> onPress) :
		UIElement(intvec2{buttonUnpressed->GetWidth(), buttonUnpressed->GetHeight()}),
		buttonUnpressed(buttonUnpressed),
		buttonHover(buttonHover),
		buttonPressed(buttonPressed),
		currentImage(buttonUnpressed),
		onPress(onPress)
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

		ButtonState newButtonState = buttonState;

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

		if (buttonState == PRESSED) {
			onPress();
		}
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

}
// A simple text input that can handle input when focused.
#pragma once

#include "UI_Text.h"
#include "Focusable.h"

class UI_TextInput : public UI_Text, public Focusable
{
private:

public:
	static const D2D1::ColorF INPUT_RECT_COLOR_DEFAULT;
	static const DWRITE_TEXT_ALIGNMENT TEXT_ALIGN_HORIZONTAL_DEFAULT;
	static const DWRITE_PARAGRAPH_ALIGNMENT TEXT_ALIGN_VERTICAL_DEFAULT;

	// Set the text and its properties. Serves as an initializer.
	// Input text fields will always start with empty strings.
	// Bottom of input bounds determined by text height.
	void init(float textSize, DWRITE_FONT_WEIGHT fontWeight,
		float left, float top, float right);

	// Return the focus of this component.
	bool hasFocus() override;
	// Set the focus of this component.
	void setFocus(bool) override;
	// Handle keypresses sent by the screen this component is a part of.
	void charIn(wchar_t key);
	// Draw the component.
	void draw(ID2D1HwndRenderTarget* pRT) override;
};

#pragma once
#include <string>

#include "UI_Text.h"
#include "Focusable.h"

class UI_ChatInput : public UI_Text, public Focusable
{
private:
	int maxTop;				// the highest we'll let the input box extend
	int lastTextHeight = 0;	// the height of the input bounds on its most recent change

public:
	static const D2D1::ColorF INPUT_RECT_COLOR_DEFAULT;
	static const DWRITE_TEXT_ALIGNMENT TEXT_ALIGN_HORIZONTAL_DEFAULT;
	static const DWRITE_PARAGRAPH_ALIGNMENT TEXT_ALIGN_VERTICAL_DEFAULT;

	// Return whether the component is focused or not.
	bool hasFocus() override;
	// Set the focus of the component.
	void setFocus(bool focused) override;
	// Set the bounds of the input rect. Position by the bottom-left coordinate. maxTop should be -1 if GROWTH_NONE is set.
	void setBounds(int maxTop, float left, float right, float bottom);
	// Set the text and format of the input.
	void setText(std::wstring text, float textSize, DWRITE_FONT_WEIGHT fontWeight);
	// Handle incoming characters and keypresses.
	void charIn(wchar_t key);
	// Draw the component.
	void draw(ID2D1HwndRenderTarget* pRT) override;
};

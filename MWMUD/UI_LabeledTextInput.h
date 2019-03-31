// A focusable text input that has a label which is highlighted when the component is in focus.
#pragma once

#include "UI_Element.h"
#include "UI_MenuOption.h"
#include "UI_TextInput.h"

#include "Focusable.h"

class UI_LabeledTextInput : public UI_Element, public Focusable
{
private:
	UI_MenuOption label;
	UI_TextInput input;
	float textSize;
	float left, top;
	int labelWidth, inputWidth;

public:

	void init(std::wstring labelText, float textSize, DWRITE_PARAGRAPH_ALIGNMENT labelHorizontalAlign,
		DWRITE_FONT_WEIGHT fontWeight, float left, float top, int labelWidth, int inputWidth);
	std::wstring getInputText();
	float getBottom();
	bool hasFocus() override;
	void setFocus(bool focused) override;
	void charIn(wchar_t key);

	void draw(ID2D1HwndRenderTarget* pRT) override;
};

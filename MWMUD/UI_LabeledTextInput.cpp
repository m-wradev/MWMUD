#include "UI_LabeledTextInput.h"

void UI_LabeledTextInput::init(std::wstring labelText, float textSize,
	DWRITE_PARAGRAPH_ALIGNMENT labelHorizontalAlign, DWRITE_FONT_WEIGHT fontWeight,
	float left, float top, int labelWidth, int inputWidth)
{
	this->textSize = textSize;
	this->left = left;
	this->top = top;
	this->labelWidth = labelWidth;
	this->inputWidth = inputWidth;

	label.setText(labelText, textSize, DWRITE_TEXT_ALIGNMENT_CENTER, labelHorizontalAlign,
		fontWeight);
	label.setBounds(left, top, left + labelWidth, top + label.getTextHeight());

	input.init(textSize, fontWeight, left + labelWidth, top,
		left + labelWidth + inputWidth);
}

std::wstring UI_LabeledTextInput::getInputText() { return input.getText(); }
float UI_LabeledTextInput::getBottom() { return input.getBounds().bottom; }
bool UI_LabeledTextInput::hasFocus() { return focused; }
void UI_LabeledTextInput::setFocus(bool focused)
{
	this->focused = focused;

	label.setFocus(focused);
	input.setFocus(focused);
}

void UI_LabeledTextInput::charIn(wchar_t key)
{
	if (focused) input.charIn(key);
}

void UI_LabeledTextInput::draw(ID2D1HwndRenderTarget* pRT)
{
	label.draw(pRT);
	input.draw(pRT);
}
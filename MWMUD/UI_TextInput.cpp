#include "UI_TextInput.h"

const D2D1::ColorF UI_TextInput::INPUT_RECT_COLOR_DEFAULT = D2D1::ColorF(D2D1::ColorF::DarkSlateGray);
const DWRITE_TEXT_ALIGNMENT UI_TextInput::TEXT_ALIGN_HORIZONTAL_DEFAULT = DWRITE_TEXT_ALIGNMENT_LEADING;
const DWRITE_PARAGRAPH_ALIGNMENT UI_TextInput::TEXT_ALIGN_VERTICAL_DEFAULT = DWRITE_PARAGRAPH_ALIGNMENT_CENTER;

void UI_TextInput::init(float textSize, DWRITE_FONT_WEIGHT fontWeight,
	float left, float top, float right)
{
	this->textSize = textSize;
	this->textAlignHorizontal = UI_TextInput::TEXT_ALIGN_HORIZONTAL_DEFAULT;
	this->textAlignVertical = UI_TextInput::TEXT_ALIGN_VERTICAL_DEFAULT;
	this->fontWeight = fontWeight;

	// init bounds for the height calculation
	setBounds(left, top, right, top);

	// Calculate the height of the input rect.
	this->text = L"Height Calc";
	setBounds(left, top, right, top + getTextHeight());
	this->text = L"";
}

bool UI_TextInput::hasFocus() { return focused; }
void UI_TextInput::setFocus(bool focused) { this->focused = focused; }

void UI_TextInput::charIn(wchar_t key)
{
	if (key >= ' ' && key <= '~')
	{
		text += key;
	}
	else if (key == VK_BACK)
	{
		if (!text.empty())
			text.pop_back();
	}
}

void UI_TextInput::draw(ID2D1HwndRenderTarget* pRT)
{
	// Only draw the input rect if the component has focus
	if (focused)
	{
		ID2D1SolidColorBrush* pBrush;
		pRT->CreateSolidColorBrush(INPUT_RECT_COLOR_DEFAULT, &pBrush);
		pRT->FillRectangle(bounds, pBrush);
		pBrush->Release();
	}

	if (!text.empty())
		UI_Text::draw(pRT);
}
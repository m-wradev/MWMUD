#include "UI_ChatInput.h"
#include "Dispatcher.h"
#include "GameEvent.h"
#include "GlobalChat.h"

const D2D1::ColorF UI_ChatInput::INPUT_RECT_COLOR_DEFAULT = D2D1::ColorF(D2D1::ColorF::DarkSlateGray);
const DWRITE_TEXT_ALIGNMENT UI_ChatInput::TEXT_ALIGN_HORIZONTAL_DEFAULT = DWRITE_TEXT_ALIGNMENT_LEADING;
const DWRITE_PARAGRAPH_ALIGNMENT UI_ChatInput::TEXT_ALIGN_VERTICAL_DEFAULT = DWRITE_PARAGRAPH_ALIGNMENT_FAR;

bool UI_ChatInput::hasFocus() { return focused; }

void UI_ChatInput::setFocus(bool focused)
{
	this->focused = focused;
}

void UI_ChatInput::setBounds(int maxTop, float left, float right, float bottom)
{
	this->maxTop = maxTop;
	UI_Text::setBounds(left, bottom, right, bottom);
}

void UI_ChatInput::setText(std::wstring text, float textSize, DWRITE_FONT_WEIGHT fontWeight)
{
	this->text = text;
	this->textSize = textSize;
	this->textAlignHorizontal = UI_ChatInput::TEXT_ALIGN_HORIZONTAL_DEFAULT;
	this->textAlignVertical = UI_ChatInput::TEXT_ALIGN_VERTICAL_DEFAULT;
	this->fontWeight = fontWeight;
}

// This component will only be notified of key pressed events if it's set as focused.
void UI_ChatInput::charIn(wchar_t key)
{
	// Only want to add characters to the input string if they're
	// alphanumeric or punctuation.
	if		(key >= ' ' && key <= '~')
	{
		text.push_back(key);

		// Recalculate the height of the rectangle to draw
		float textHeight = getTextHeight();
		float prevTop = bounds.top;
		bounds.top = bounds.bottom - textHeight;
		// Don't let the input rect extend past maxTop.
		// If it does, just pop off the most recent character
		// and adjust the bounds.
		if (bounds.top < maxTop)
		{
			text.pop_back();
			bounds.top = prevTop;
		}
	}
	else if (key == VK_BACK)
	{
		if (!text.empty())
			text.pop_back();

		// Recalculate the height of the rectangle to draw
		if (text.empty())
			bounds.top = bounds.bottom;
		else
			bounds.top = bounds.bottom - (int)getTextHeight();
	}
	else if (key == VK_RETURN)
	{
		// TODO: Strip leading and trailing whitespace
		if (!text.empty())
			GlobalChat::parse(UI_Text::text);

		text.clear();
		bounds.top = bounds.bottom;
	}

	// The size of the input bounds will only change as a result of receiving a keypressed notification
	// Check to see if the size changed, and if so, send a message saying that it did.
	int currentTextHeight = (text.empty()) ? 0 : (int)getTextHeight();
	if (lastTextHeight != currentTextHeight)
	{
		std::string info = (currentTextHeight - lastTextHeight > 0) ? "grow" : "shrink";
		Dispatcher::enqueueEvent (new UIEvent(EVENT_TYPE::GEVT_UI_TEXTINPUT_HEIGHTCHANGED, this, info));
		lastTextHeight = currentTextHeight;
	}
}

void UI_ChatInput::draw(ID2D1HwndRenderTarget* pRT)
{
	// Draw the input rectangle first
	ID2D1SolidColorBrush* pBrush;
	pRT->CreateSolidColorBrush(INPUT_RECT_COLOR_DEFAULT, &pBrush);
	pRT->FillRectangle(bounds, pBrush);
	pBrush->Release();

	if (!text.empty())
		UI_Text::draw(pRT);
}
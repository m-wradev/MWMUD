#include "UI_TextInput.h"
#include "Dispatcher.h"

const D2D1::ColorF UI_TextInput::INPUT_RECT_COLOR_DEFAULT = D2D1::ColorF(D2D1::ColorF::DarkSlateGray);
const DWRITE_TEXT_ALIGNMENT UI_TextInput::TEXT_ALIGN_VERTICAL_DEFAULT = DWRITE_TEXT_ALIGNMENT_LEADING;
const DWRITE_PARAGRAPH_ALIGNMENT UI_TextInput::TEXT_ALIGN_HORIZONTAL_DEFAULT = DWRITE_PARAGRAPH_ALIGNMENT_FAR;

UI_TextInput::~UI_TextInput()
{
	Dispatcher::unsubscribe(EVENT_TYPE::GEVT_INPUT_KEYPRESSED, this);
}

void UI_TextInput::setFocused(bool focused)
{
	this->focused = focused;

	if (focused)
		Dispatcher::subscribe(EVENT_TYPE::GEVT_INPUT_KEYPRESSED, this);
	else
		Dispatcher::unsubscribe(EVENT_TYPE::GEVT_INPUT_KEYPRESSED, this);
}

void UI_TextInput::setBounds(float left, float right, float bottom)
{
	UI_Text::setBounds(left, bottom, right, bottom);
}

void UI_TextInput::setText(std::wstring text, float textSize, DWRITE_FONT_WEIGHT fontWeight)
{
	this->text = text;
	this->textSize = textSize;
	this->textAlignHorizontal = UI_TextInput::TEXT_ALIGN_VERTICAL_DEFAULT;
	this->textAlignVertical = UI_TextInput::TEXT_ALIGN_HORIZONTAL_DEFAULT;
	this->fontWeight = fontWeight;
}

// This component will only be notified of key pressed events if it's set as focused.
void UI_TextInput::onNotify(GameEvent* evt)
{
	wchar_t key = static_cast<InputEvent*>(evt)->key;

	// Only want to add characters to the input string if they're
	// alphanumeric or punctuation.
	if		(key >= ' ' && key <= '~')
	{
		text.push_back(key);

		// Recalculate the height of the rectangle to draw
		bounds.top = bounds.bottom - (int)getTextHeight();
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
			Dispatcher::notify(new ChatEvent(EVENT_TYPE::GEVT_CHAT_MESSAGE_SENT, UI_Text::text));

		text.clear();
		bounds.top = bounds.bottom;
	}

	// The size of the input bounds will only change as a result of receiving a keypressed notification
	// Check to see if the size changed, and if so, send a message saying that it did.
	int currentTextHeight = (text.empty()) ? 0 : (int)getTextHeight();
	if (lastTextHeight != currentTextHeight)
	{
		std::string info = (currentTextHeight - lastTextHeight > 0) ? "grow" : "shrink";
		Dispatcher::notify(new UIEvent(EVENT_TYPE::GEVT_UI_TEXTINPUT_HEIGHTCHANGED, this, info));
		lastTextHeight = currentTextHeight;
	}
}

void UI_TextInput::draw(ID2D1HwndRenderTarget* pRT)
{
	// Draw the input rectangle first
	ID2D1SolidColorBrush* pBrush;
	pRT->CreateSolidColorBrush(INPUT_RECT_COLOR_DEFAULT, &pBrush);
	pRT->FillRectangle(bounds, pBrush);
	pBrush->Release();

	if (!text.empty())
		UI_Text::draw(pRT);
}
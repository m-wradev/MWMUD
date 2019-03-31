#include "UI_Chatbox.h"

#include "Dispatcher.h"

UI_Chatbox::UI_Chatbox()
{
	Dispatcher::subscribe(EVENT_TYPE::GEVT_CHAT_MESSAGESEND, this);
}

UI_Chatbox::~UI_Chatbox()
{
	Dispatcher::unsubscribe(EVENT_TYPE::GEVT_CHAT_MESSAGESEND, this);
}

void UI_Chatbox::set(int inputTextSize,
	DWRITE_TEXT_ALIGNMENT inputTextAlignHorizontal,
	DWRITE_PARAGRAPH_ALIGNMENT inputTextAlignVertical,
	DWRITE_FONT_WEIGHT inputFontWeight,
	int outputTextSize,
	DWRITE_TEXT_ALIGNMENT outputTextAlignHorizontal,
	DWRITE_PARAGRAPH_ALIGNMENT outputTextAlignVertical,
	DWRITE_FONT_WEIGHT outputFontWeight,
	int left, int top, int right, int bottom)
{
	chatInput.setText(L"", inputTextSize, inputFontWeight);
	chatInput.setBounds(top, left, right, bottom);

	chatOutput.set(outputTextSize, left, top, right, bottom);
}

bool UI_Chatbox::hasFocus() { return focused; }
UI_ChatInput& UI_Chatbox::getInputComponent() { return chatInput; }
UI_ChatOutput& UI_Chatbox::getOutputComponent() { return chatOutput; }

void UI_Chatbox::setFocus(bool focused)
{
	this->focused = focused;
	chatInput.setFocus(focused);
}

void UI_Chatbox::handleCharInput(wchar_t key)
{
	if (chatInput.hasFocus()) chatInput.charIn(key);
}

void UI_Chatbox::onNotify(GameEvent* gevt)
{
	if (gevt->eventType == EVENT_TYPE::GEVT_CHAT_MESSAGESEND)
	{
		chatOutput.push_back(static_cast<ChatEvent*>(gevt)->message);
	}
}

void UI_Chatbox::draw(ID2D1HwndRenderTarget* pRT)
{
	chatOutput.draw(pRT);
	chatInput.draw(pRT);
}
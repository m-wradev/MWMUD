#include "UI_Chatbox.h"

#include "Dispatcher.h"

UI_Chatbox::UI_Chatbox()
{
	Dispatcher::subscribe(EVENT_TYPE::GEVT_CHAT_MESSAGE_SENT, this);
}

UI_Chatbox::~UI_Chatbox()
{
	Dispatcher::unsubscribe(EVENT_TYPE::GEVT_CHAT_MESSAGE_SENT, this);
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
	chatInput.setBounds(left, right, bottom);

	chatOutput.set(outputTextSize, outputTextAlignHorizontal, outputTextAlignVertical,
		outputFontWeight, 5, left, top, right);
}

UI_TextInput& UI_Chatbox::getInputComponent() { return chatInput; }
UI_VerticalList<UI_Text>& UI_Chatbox::getOutputComponent() { return chatOutput; }

void UI_Chatbox::onNotify(GameEvent* gevt)
{
	if		(gevt->eventType == EVENT_TYPE::GEVT_UI_TEXTINPUT_HEIGHTCHANGED)
	{
	}
	else if (gevt->eventType == EVENT_TYPE::GEVT_CHAT_MESSAGE_SENT)
	{
		chatOutput.addElement(static_cast<ChatEvent*>(gevt)->message);
	}
}

void UI_Chatbox::draw(ID2D1HwndRenderTarget* pRT)
{
	chatOutput.draw(pRT);
	chatInput.draw(pRT);
}
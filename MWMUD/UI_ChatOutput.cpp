#include "UI_ChatOutput.h"
#include "UI_TextInput.h"

#include "Dispatcher.h"

UI_ChatOutput::UI_ChatOutput()
{
	Dispatcher::subscribe(EVENT_TYPE::GEVT_UI_TEXTINPUT_HEIGHTCHANGED, this);
}

UI_ChatOutput::~UI_ChatOutput()
{
	Dispatcher::unsubscribe(EVENT_TYPE::GEVT_UI_TEXTINPUT_HEIGHTCHANGED, this);
}

void UI_ChatOutput::set(int textSize, int left, int top, int right, int bottom)
{
	this->textSize = textSize;
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;

	renderedMessages.set(textSize, DWRITE_TEXT_ALIGNMENT_LEADING,
		DWRITE_PARAGRAPH_ALIGNMENT_CENTER, DWRITE_FONT_WEIGHT_NORMAL,
		0, left, top, right);
}

void UI_ChatOutput::push_back(std::wstring text)
{
	// Enforce max history limit
	if (messageHistory.size() >= maxHistory)
		messageHistory.pop_front();
	messageHistory.push_back(text);

	// Initialize renderStart when the first message is pushed in.
	// hiddenBoundary is set to the same element as renderStart.
	if (messageHistory.size() == 1)
	{
		renderStart = messageHistory.begin();
		hiddenBoundary = renderStart;
	}

	// Only keep the most recent (and visible) messages in the vertical list
	renderedMessages.push_back(text);
	if (top + renderedMessages.getHeight() >= bottom)
	{
		renderedMessages.pop_front();
		renderStart++;
	}
}

void UI_ChatOutput::onNotify(GameEvent* gevt)
{
	if (gevt->eventType == EVENT_TYPE::GEVT_UI_TEXTINPUT_HEIGHTCHANGED)
	{
		// If we're worried about text input height changes, then the bottom of this container
		// will always be the top of its paired text input.
		bottom = dynamic_cast<UI_TextInput*>(static_cast<UIEvent*>(gevt)->element)->getBounds().top;

		if (messageHistory.size() > 0)
		{
			std::string info = static_cast<UIEvent*>(gevt)->info;

			if (info == "grow")
			{
				if (top + renderedMessages.getHeight() >= bottom)
				{
					// The input text field's height is blocking the most recent message,
					// so we have to make room for the message by removing the first rendered
					// message and increasing the hidden boundary by 1.
					renderedMessages.pop_front();
					hiddenBoundary++;
				}
			}
			else if (info == "shrink")
			{
				if (hiddenBoundary != renderStart && hiddenBoundary != messageHistory.begin())
				{
					// If hidden boundary isn't the same as renderStart then we can decrement
					// the boundary and push the previously hidden message back onto the
					// list to be rendered.
					hiddenBoundary--;
					renderedMessages.push_front(*hiddenBoundary);
				}
			}
		}
	}
}

void UI_ChatOutput::draw(ID2D1HwndRenderTarget* pRT)
{
	renderedMessages.draw(pRT);
}

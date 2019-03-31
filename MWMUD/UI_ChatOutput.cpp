// TODO - Fix bug where shrinking the input rect can cause the incorrect message to be placed at the top of the screen.
// TODO - Make it so that a renderedMessages with element offsets will render correctly when they hit the bottom of the screen and the input rect height changes.
#include "UI_ChatOutput.h"
#include "UI_ChatInput.h"

#include "Dispatcher.h"
#include "GlobalChat.h"

UI_ChatOutput::UI_ChatOutput()
{
	renderStart = 0;
	hiddenBoundary = 0;

	Dispatcher::subscribe(EVENT_TYPE::GEVT_UI_TEXTINPUT_HEIGHTCHANGED, this);
	Dispatcher::subscribe(EVENT_TYPE::GEVT_CHAT_CLEARCHAT, this);
}

UI_ChatOutput::~UI_ChatOutput()
{
	Dispatcher::unsubscribe(EVENT_TYPE::GEVT_CHAT_CLEARCHAT, this);
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
		5, left, top, right);
}

void UI_ChatOutput::push_back(std::wstring text)
{
	// Enforce max history limit
	if (messageHistory.size() >= maxHistory)
	{
		messageHistory.pop_front();

		// Only care to remove messages at this point if for some reason the
		// max message history means that the chatoutput can't fill with
		// messages completely.
		if (renderedMessages.getHeight() < bottom)
			renderedMessages.pop_front();
	}
	messageHistory.push_back(text);

	// Only keep the most recent (and visible) messages in the vertical list
	renderedMessages.push_back(text);
	if (top + renderedMessages.getHeight() > bottom)
	{
		while (top + renderedMessages.getHeight() > bottom)
		{
			renderedMessages.pop_front();
			renderStart++;
		}

		hiddenBoundary = renderStart;
	}
}

void UI_ChatOutput::onNotify(GameEvent* gevt)
{
	// TEXT INPUT HEIGHT CHANGED
	if (gevt->eventType == EVENT_TYPE::GEVT_UI_TEXTINPUT_HEIGHTCHANGED)
	{
		// If we're worried about text input height changes, then the bottom of this container
		// will always be the top of its paired text input.
		bottom = dynamic_cast<UI_ChatInput*>(static_cast<UIEvent*>(gevt)->element)->getBounds().top;

		if (messageHistory.size() > 0)
		{
			std::string info = static_cast<UIEvent*>(gevt)->info;

			if (info == "grow")
			{
				while (top + renderedMessages.getHeight() > bottom)
				{
					// The input text field's height is blocking the most recent message,
					// so we have to make room for the message by removing the first rendered
					// message and increasing the hidden boundary by 1.
					hiddenBoundary++;
					renderedMessages.pop_front();
				}
			}
			else if (info == "shrink")
			{
				if (renderStart != hiddenBoundary && hiddenBoundary != 0)
				{
					// If hidden boundary isn't the same as renderStart then we can decrement
					// the boundary and push the previously hidden message back onto the
					// list to be rendered.
					while (hiddenBoundary != renderStart)
					{
						hiddenBoundary--;
						renderedMessages.push_front(messageHistory[hiddenBoundary]);

						if (top + renderedMessages.getHeight() > bottom)
						{
							hiddenBoundary++;
							renderedMessages.pop_front();
							break;
						}
					}
				}
			}
		}
	}

	// CLEAR CHAT
	else if (gevt->eventType == EVENT_TYPE::GEVT_CHAT_CLEARCHAT)
	{
		renderStart = 0;
		hiddenBoundary = 0;
		messageHistory.clear();
		renderedMessages.clear();
	}
}

void UI_ChatOutput::draw(ID2D1HwndRenderTarget* pRT)
{
	renderedMessages.draw(pRT);
}

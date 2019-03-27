// TODO: add support for scrolling through message history
#pragma once
#include <string>
#include <list>

#include "UI_Element.h"
#include "UI_Text.h"
#include "UI_VerticalList.h"

#include "Listener.h"
#include "GameEvent.h"

class UI_ChatOutput : public UI_Element, public Listener
{
private:
	std::list<std::wstring> messageHistory;
	std::list<std::wstring>::iterator renderStart; // keeps track of the beginning of rendered message history
	std::list<std::wstring>::iterator hiddenBoundary;	// keeps track of the line between hidden and rendered messages
	UI_VerticalList<UI_Text> renderedMessages;

	int textSize;
	int left, top, right, bottom;

public:
	static const int maxHistory = 200; // max number of messages that can be stored

	UI_ChatOutput();
	~UI_ChatOutput();

	// Set values
	void set(int textSize, int left, int top, int right, int bottom);
	//void setBottom(int bottom);

	// Add an element to the message history.
	// If an element's bounds exceed the bottom of the container, 
	// then messages are moved up the screen to make room.
	// Messages that exceed the top of the screen are not rendered.
	void push_back(std::wstring text);

	void onNotify(GameEvent* gevt) override;

	// Draw the component
	void draw(ID2D1HwndRenderTarget* pRT) override;
};
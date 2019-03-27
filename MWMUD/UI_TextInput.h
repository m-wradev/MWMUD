// TODO: enforce max character limit
#pragma once
#include "UI_Text.h"
#include "string"

#include "Listener.h"
#include "GameEvent.h"

class UI_TextInput : public UI_Text, public Listener
{
private:
	int lastTextHeight = 0;	// the height of the input bounds on its most recent change
	bool focused = false;	// is this textinput currently in focus for receiving input?

public:
	static const D2D1::ColorF INPUT_RECT_COLOR_DEFAULT;
	static const DWRITE_TEXT_ALIGNMENT TEXT_ALIGN_VERTICAL_DEFAULT;
	static const DWRITE_PARAGRAPH_ALIGNMENT TEXT_ALIGN_HORIZONTAL_DEFAULT;

	~UI_TextInput();

	// set the focus of the component
	// When focus is set, the component will subscribe to keypressed events
	// If focus is taken away (focused is false), it will unsubscribe from the event
	void setFocused(bool focused);
	// Set the bounds of the input rect. Position by the bottom-left coordinate.
	void setBounds(float left, float right, float bottom);
	// Set the text and format of the input.
	void setText(std::wstring text, float textSize, DWRITE_FONT_WEIGHT fontWeight);

	void onNotify(GameEvent* evt) override;
	void draw(ID2D1HwndRenderTarget* pRT) override;
};

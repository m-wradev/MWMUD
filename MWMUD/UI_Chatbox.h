#pragma once

#include "UI_Element.h"
#include "UI_Text.h"
#include "UI_ChatInput.h"
#include "UI_VerticalList.h"
#include "UI_ChatOutput.h"

#include "Focusable.h"

#include "GameEvent.h"
#include "Listener.h"

class UI_Chatbox : public UI_Element, public Listener, public Focusable
{
private:
	UI_ChatOutput chatOutput;
	UI_ChatInput chatInput;
	float left, top, right, bottom;

public:
	UI_Chatbox();
	~UI_Chatbox();

	void set(int inputTextSize,
		DWRITE_TEXT_ALIGNMENT inputTextAlignHorizontal,
		DWRITE_PARAGRAPH_ALIGNMENT inputTextAlignVertical,
		DWRITE_FONT_WEIGHT inputFontWeight,
		int outputTextSize,
		DWRITE_TEXT_ALIGNMENT outputTextAlignHorizontal,
		DWRITE_PARAGRAPH_ALIGNMENT outputTextAlignVertical,
		DWRITE_FONT_WEIGHT outputFontWeight,
		int left, int top, int right, int bottom);

	UI_ChatInput& getInputComponent();
	UI_ChatOutput& getOutputComponent();

	bool hasFocus() override;
	void setFocus(bool focus) override;

	// Handle character input.
	void handleCharInput(wchar_t key);

	void onNotify(GameEvent* gevt) override;
	void draw(ID2D1HwndRenderTarget* pRT) override;
};

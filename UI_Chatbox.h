#pragma once

#include "UI_Element.h"
#include "UI_Text.h"
#include "UI_TextInput.h"
#include "UI_VerticalList.h"

#include "GameEvent.h"
#include "Listener.h"

class UI_Chatbox : public UI_Element, public Listener
{
private:
	UI_VerticalList<UI_Text> chatOutput;
	UI_TextInput chatInput;
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

	UI_TextInput& getInputComponent();
	UI_VerticalList<UI_Text>& getOutputComponent();

	void onNotify(GameEvent* gevt) override;
	void draw(ID2D1HwndRenderTarget* pRT) override;
};


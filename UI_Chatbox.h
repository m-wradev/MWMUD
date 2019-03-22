#pragma once

#include "UI_Element.h"
#include "UI_Text.h"
#include "UI_TextInput.h"
#include "UI_VerticalList.h"

#include "Listener.h"
#include "GameEvent.h"

class UI_Chatbox : public UI_Element, public Listener
{
private:
	UI_VerticalList<UI_Text> chatOutput;
	UI_TextInput chatInput;
	float top, left, right, bottom;

public:

	void setBounds(float left, float top, float right, float bottom);
	void onNotify(GameEvent* evt) override;
	void draw(ID2D1HwndRenderTarget* pRT) override;
};


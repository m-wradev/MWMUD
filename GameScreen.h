#pragma once

#include "Screen.h"
#include "UI_Chatbox.h"
/*
#include "UI_Text.h"
#include "UI_VerticalList.h"
#include "UI_TextInput.h"
*/

class GameScreen : public Screen
{
private:
	/*
	UI_VerticalList<UI_Text> textOut;
	UI_TextInput textIn;
	*/
	UI_Chatbox chatbox;

public:
	GameScreen();

	void handleKeypress(wchar_t key) override;
	void draw(ID2D1HwndRenderTarget* pRT) override;
};
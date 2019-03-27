#pragma once

#include "Screen.h"
#include "UI_Chatbox.h"

class GameScreen : public Screen
{
private:
	UI_Chatbox chatbox;

public:
	GameScreen();

	void handleKeypress(wchar_t key) override;
	void draw(ID2D1HwndRenderTarget* pRT) override;
};
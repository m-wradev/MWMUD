#pragma once

#include "Screen.h"
#include "UI_Text.h"

class TitleScreen : public Screen
{
private:
	UI_Text title;
	UI_Text version;
	UI_Text prompt;

public:
	TitleScreen();

	// handle keypresses detected by the application
	void handleKeypress(wchar_t key) override;

	// Draw the screen
	void draw(ID2D1HwndRenderTarget* pRT) override;
};


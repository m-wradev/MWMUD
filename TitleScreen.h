#pragma once

#include "Screen.h"
#include "UI_Label.h"

class TitleScreen : public Screen
{
private:
	UI_Label title;
	UI_Label version;
	UI_Label prompt;

public:
	TitleScreen();

	// handle keypresses detected by the application
	void handleKeypress(char) override;

	// Draw the screen
	void draw(HWND) override;
};


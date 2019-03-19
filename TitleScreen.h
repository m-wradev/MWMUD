#pragma once
#include "Screen.h"

class TitleScreen : public Screen
{
private:
	RECT titleRect;			// Defines position of the application name
	RECT versionRect;		// Defines position of the application version
	RECT startPromptRect;	// Defines position of the start prompt

	HFONT titleFont;
	HFONT versionFont;
	HFONT startPromptFont;

public:
	TitleScreen();
	~TitleScreen();

	// handle keypresses detected by the application
	void handleKeypress(char) override;

	// Draw the screen
	void draw(HWND) override;
};


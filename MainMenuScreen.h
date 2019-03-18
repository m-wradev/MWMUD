#pragma once
#include "Screen.h"
class MainMenuScreen : public Screen
{
private:
	RECT titleRect;
	RECT playRect;
	RECT optionsRect;
	RECT exitRect;

	HFONT titleFont;
	HFONT menuItemsFont;

public:
	MainMenuScreen();
	~MainMenuScreen();

	void draw(HWND) override;
};


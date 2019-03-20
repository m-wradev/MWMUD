#pragma once
#include "Screen.h"
#include "UI_MenuOptionListVertical.h"

#include <list>

class MainMenuScreen : public Screen
{
private:
	
	// UI ELEMENTS
	UI_Label titleLabel;
	UI_MenuOptionListVertical menuOptions;

	std::list<UI_MenuOption>::iterator highlightedOption;

public:
	MainMenuScreen();

	// handle keypresses detected by the application 
	void handleKeypress(char) override;
	
	// draw the screen
	void draw(HWND) override;
};


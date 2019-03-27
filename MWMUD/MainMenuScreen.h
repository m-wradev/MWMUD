#pragma once
#include <list>

#include "Screen.h"
#include "UI_MenuOption.h"
#include "UI_VerticalList.h"

class MainMenuScreen : public Screen
{
private:
	
	// UI ELEMENTS
	UI_Text title;
	UI_Text version;
	UI_VerticalList<UI_MenuOption> menuOptions;

	std::list<UI_MenuOption>::iterator highlightedOption;

public:
	MainMenuScreen();

	// handle keypresses detected by the application 
	void handleKeypress(wchar_t key) override;
	
	// draw the screen
	void draw(ID2D1HwndRenderTarget* pRT) override;
};


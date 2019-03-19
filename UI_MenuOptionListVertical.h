#pragma once
#include <Windows.h>
#include <list>

#include "UI_MenuOption.h"

class UI_MenuOptionListVertical
{
private:
	std::list<UI_MenuOption> menuOptions;

	int fontSize;		// font size of each menu option
	UINT fontAlignment;	// flags representing font's alignment
	int optionHeight;	// height of each option's bounds RECT
	int top;			// y coord of the top-left corner
	int left;			// x coord of the top-left corner
	int right;			// x coord of the right side

public:
	UI_MenuOptionListVertical();
	~UI_MenuOptionListVertical();

	// set all variables
	void set(int fontSize, UINT fontAlignment, int optionHeight, int left, int top, int right);

	// retrieve the menu options
	std::list<UI_MenuOption>* getOptions();

	// Add a UI_MenuOption to menuOptions. set() should be called before calling this method.		
	// TODO: modify this to also pass in a callback function/event handler
	void addOption(std::string label);

	// Draw this UI element
	void draw(HWND hWnd);
};

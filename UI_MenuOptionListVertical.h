#pragma once

#include "UI_MenuOption.h"

#include <Windows.h>
#include <list>

class UI_MenuOptionListVertical : UI_Element
{
private:
	std::list<UI_MenuOption> menuOptions;

	int fontSize;		// font size of each menu option
	UINT textAlign;		// flags representing font's alignment
	int optionHeight;	// height of each option's bounds RECT
	int top;			// y coord of the top-left corner
	int left;			// x coord of the top-left corner
	int right;			// x coord of the right side

public:
	void set(int fontSize, UINT fontAlignment, int optionHeight, int left, int top, int right);

	std::list<UI_MenuOption>* getOptions();

	// Add a UI_MenuOption to menuOptions. set() should be called before calling this method.		
	// TODO: modify this to also pass in a callback function/event handler
	UI_MenuOption addOption(std::string optionText, void(*onSelect)(void));

	// Draw this UI element
	void draw(HWND hWnd) override;
};

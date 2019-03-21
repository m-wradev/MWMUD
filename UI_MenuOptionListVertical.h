#pragma once

#include "UI_MenuOption.h"

#include <Windows.h>
#include <list>

class UI_MenuOptionListVertical : UI_Element
{
private:
	std::list<UI_MenuOption> menuOptions;

	/*
	int fontSize;		// font size of each menu option
	UINT textAlign;		// flags representing font's alignment
	int optionHeight;	// height of each option's bounds RECT
	int top;			// y coord of the top-left corner
	int left;			// x coord of the top-left corner
	int right;			// x coord of the right side
	*/
	int fontSize;									// font size of each menu item
	DWRITE_TEXT_ALIGNMENT textAlignHorizontal;		// text's horizontal alignment
	DWRITE_PARAGRAPH_ALIGNMENT textAlignVertical;	// text's vertical alignment
	int optionHeight;								// height of each option's bounds rect
	int top;										// y coord of top-left corner
	int left;										// x coord of top-left corner
	int right;										// x coord of right side

public:
	//void set(int fontSize, UINT fontAlignment, int optionHeight, int left, int top, int right);
	void set(int fontSize, DWRITE_TEXT_ALIGNMENT textAlignHorizontal,
		DWRITE_PARAGRAPH_ALIGNMENT textAlignVertical, int optionHeight,
		int left, int top, int right);

	std::list<UI_MenuOption>* getOptions();

	// Add a UI_MenuOption to menuOptions. set() should be called before calling this method.		
	// TODO: modify this to also pass in a callback function/event handler
	UI_MenuOption addOption(std::wstring optionText, void(*onSelect)(void));

	// Draw this UI element
	void draw(ID2D1HwndRenderTarget* pRT) override;
};

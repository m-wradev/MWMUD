#include "UI_MenuOptionListVertical.h"

UI_MenuOptionListVertical::UI_MenuOptionListVertical()
{
}

UI_MenuOptionListVertical::~UI_MenuOptionListVertical()
{
}

void UI_MenuOptionListVertical::set(int fontSize, UINT fontAlignment, int optionHeight, 
									int left, int top, int right)
{
	this->fontSize = fontSize;
	this->fontAlignment = fontAlignment;
	this->optionHeight = optionHeight;
	this->left = left;
	this->top = top;
	this->right = right;
}

std::list<UI_MenuOption>* UI_MenuOptionListVertical::getOptions()
{
	return &menuOptions;
}

void UI_MenuOptionListVertical::addOption(std::string labelText)
{
	UI_MenuOption mo(labelText, fontSize, fontAlignment);
	
	// Calculate vertical position of the new menu option
	if (menuOptions.size() > 0)
		mo.setBounds(left, menuOptions.back().getBounds().bottom, right, menuOptions.back().getBounds().bottom + optionHeight);
	else
		mo.setBounds(left, top, right, top + optionHeight);

	// push the menu option to the back of the deque
	menuOptions.push_back(mo);
}

void UI_MenuOptionListVertical::draw(HWND hWnd)
{
	for (UI_MenuOption mo : menuOptions)
		mo.draw(hWnd);
}

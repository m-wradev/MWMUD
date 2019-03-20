#include "UI_MenuOptionListVertical.h"

void UI_MenuOptionListVertical::set(int fontSize, UINT textAlign, int optionHeight, 
									int left, int top, int right)
{
	this->fontSize = fontSize;
	this->textAlign = textAlign;
	this->optionHeight = optionHeight;
	this->left = left;
	this->top = top;
	this->right = right;
}

std::list<UI_MenuOption>* UI_MenuOptionListVertical::getOptions()
{
	return &menuOptions;
}

UI_MenuOption UI_MenuOptionListVertical::addOption(std::string optionText, void(*onSelect)(void))
{
	UI_MenuOption mo;
	mo.setText(optionText, fontSize, textAlign, FW_LIGHT);
	mo.setCallback(onSelect);

	// Calculate vertical position of the new menu option
	if (menuOptions.size() > 0)
		mo.setBounds(left, menuOptions.back().getBounds().bottom, right, menuOptions.back().getBounds().bottom + optionHeight);
	else
		mo.setBounds(left, top, right, top + optionHeight);

	// push the menu option to the back of the deque
	menuOptions.push_back(mo);
	return mo;
}

void UI_MenuOptionListVertical::draw(HWND hWnd)
{
	for (UI_MenuOption mo : menuOptions)
		mo.draw(hWnd);
}

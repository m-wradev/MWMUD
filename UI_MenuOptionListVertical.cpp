#include "UI_MenuOptionListVertical.h"

// Set all variables
void UI_MenuOptionListVertical::set(int fontSize, DWRITE_TEXT_ALIGNMENT textAlignHorizontal,
	DWRITE_PARAGRAPH_ALIGNMENT textAlignVertical, int optionHeight, int left, int top, int right)
{
	this->fontSize = fontSize;
	this->textAlignHorizontal = textAlignHorizontal;
	this->textAlignVertical = textAlignVertical;
	this->optionHeight = optionHeight;
	this->left = left;
	this->top = top;
	this->right = right;
}

// Get the options
std::list<UI_MenuOption>* UI_MenuOptionListVertical::getOptions()
{
	return &menuOptions;
}

// Add an option, providing a callback for each added item
UI_MenuOption UI_MenuOptionListVertical::addOption(std::wstring optionText, void(*onSelect)(void))
{
	UI_MenuOption mo;
	//mo.setText(optionText, fontSize, textAlign, FW_LIGHT);
	mo.setText(optionText, fontSize, textAlignHorizontal, textAlignVertical, DWRITE_FONT_WEIGHT_NORMAL);
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

void UI_MenuOptionListVertical::draw(ID2D1HwndRenderTarget* pRT)
{
	for (UI_MenuOption mo : menuOptions)
		mo.draw(pRT);
}

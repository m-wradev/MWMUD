/* UI_MenuOptions are selectable menu options that can be set as highlighted and selected.
 * They are essentially just a UI_Label with the ability to be selected.
 */
#pragma once
#include "UI_Label.h"

class UI_MenuOption : public UI_Label
{
public:
	static const COLORREF TEXT_COLOR_HIGHLIGHTED = RGB(255, 255, 0);

private:
	typedef void(*callback)(void);

	bool highlighted = false;	// whether the option is currently highlighted
	callback onSelect;
	
public:
	UI_MenuOption() {};
	void setHighlighted(bool highlighted);
	void setCallback(callback onSelect);

	void select();
	void draw(HWND hWnd) override;
};


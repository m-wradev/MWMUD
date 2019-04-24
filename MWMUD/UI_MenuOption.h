/* UI_MenuOptions are selectable menu options that can be set as highlighted and selected.
 * They are essentially just a UI_Text with the ability to be selected.
 */
#pragma once
#include <functional>

#include "UI_Text.h"
#include "Focusable.h"

class UI_MenuOption : public UI_Text, public Focusable
{
public:
	static const D2D1::ColorF TEXT_COLOR_HIGHLIGHTED;

private:
	//typedef void(*callback)(void);

	//bool highlighted = false;	// whether the option is currently highlighted
	//callback onSelect;
	std::function<void()> onSelect;
	
public:
	UI_MenuOption() {};

	bool hasFocus() override;
	void setFocus(bool focused) override;
	//void setCallback(callback onSelect);
	void setCallback(std::function<void()> onSelect);

	void select();
	void draw(ID2D1HwndRenderTarget* pRT) override;
};


#include "UI_MenuOption.h"

#include "GameMessage.h"
#include "Dispatcher.h"
#include "TitleScreen.h"

void UI_MenuOption::setHighlighted(bool highlighted)
{
	this->highlighted = highlighted;
}

void UI_MenuOption::setCallback(callback onSelect)
{
	this->onSelect = onSelect;
}

void UI_MenuOption::select()
{
	onSelect();
}

void UI_MenuOption::draw(HWND hWnd)
{
	HDC hdc = GetDC(hWnd);
	HFONT hFont = CreateFont(textSize, 0, 0, 0, fontWeight, 0, 0, 0, 0, 0, 0, 0, 0, "SYSTEM_FIXED_FONT");

	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, (highlighted) ? UI_MenuOption::TEXT_COLOR_HIGHLIGHTED : UI_Label::TEXT_COLOR_DEFAULT);
	SelectObject(hdc, hFont);
	DrawText
	(
		hdc, 
		(highlighted) ? ("+ " + text + " +").c_str() : text.c_str(),
		-1, 
		&bounds, 
		textAlign
	);

	DeleteObject(hFont);
}

#include "UI_MenuOption.h"

UI_MenuOption::UI_MenuOption(std::string labelText, int labelFontSize, int labelFontAlignment,
							 bool highlighted)
{
	this->labelText = labelText;
	this->labelFontSize = labelFontSize;
	this->labelFontAlignment = labelFontAlignment;
	this->highlighted = false;
}

UI_MenuOption::~UI_MenuOption()
{
}

void UI_MenuOption::set(std::string labelText, int labelFontSize, UINT labelFontAlignment, 
						int left, int top, int right, int bottom, bool highlighted)
{
	this->labelText = labelText;
	this->labelFontSize = labelFontSize;
	this->labelFontAlignment = labelFontAlignment;

	bounds.left = left;
	bounds.top = top;
	bounds.right = right;
	bounds.bottom = bottom;

	this->highlighted = highlighted;
}

void UI_MenuOption::setBounds(int left, int top, int right, int bottom)
{
	bounds.left = left;
	bounds.top = top;
	bounds.right = right;
	bounds.bottom = bottom;
}

void UI_MenuOption::setHighlighted(bool highlighted)
{
	this->highlighted = highlighted;
}

std::string UI_MenuOption::getLabelText() const
{
	return labelText;
}

RECT UI_MenuOption::getBounds() const
{
	return bounds;
}

void UI_MenuOption::draw(HWND hWnd)
{
	HDC hdc = GetDC(hWnd);
	HFONT hFont = CreateFont(labelFontSize, 0, 0, 0, FW_LIGHT, 0, 0, 0, 0, 0, 0, 0, 0, "SYSTEM_FIXED_FONT");

	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, (highlighted) ? UI_MenuOption::COLOR_HIGHLIGHTED : UI_MenuOption::COLOR_DEFAULT);
	SelectObject(hdc, hFont);
	DrawText
	(
		hdc, 
		(highlighted) ? ("+ " + labelText + " +").c_str() : labelText.c_str(),
		-1, 
		&bounds, 
		labelFontAlignment
	);

	DeleteObject(hFont);
}

#include "UI_Label.h"

void UI_Label::setText(std::string text, int textSize, UINT textAlign, UINT fontWeight)
{
	this->text = text;
	this->textSize = textSize;
	this->textAlign = textAlign;
	this->fontWeight = fontWeight;
}

void UI_Label::setBounds(int left, int top, int right, int bottom)
{
	bounds.left = left;
	bounds.top = top;
	bounds.right = right;
	bounds.bottom = bottom;
}

std::string UI_Label::getText() const	{ return text; }
RECT UI_Label::getBounds() const		{ return bounds; }


void UI_Label::draw(HWND hWnd)
{
	HDC hdc = GetDC(hWnd);
	HFONT hFont = CreateFont(textSize, 0, 0, 0, fontWeight, 0, 0, 0, 0, 0, 0, 0, 0, "SYSTEM_FIXED_FONT");

	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, UI_Label::TEXT_COLOR_DEFAULT);
	SelectObject(hdc, hFont);
	DrawText(hdc, text.c_str(), -1, &bounds, textAlign);

	DeleteObject(hFont);
}
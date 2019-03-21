#include "UI_MenuOption.h"

#include "GameMessage.h"
#include "Dispatcher.h"
#include "TitleScreen.h"

const D2D1::ColorF UI_MenuOption::TEXT_COLOR_HIGHLIGHTED = D2D1::ColorF(D2D1::ColorF::Yellow);

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

void UI_MenuOption::draw(ID2D1HwndRenderTarget* pRT)
{
	/*
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
	*/
	IDWriteTextFormat* pTextFormat;
	ID2D1SolidColorBrush* pBrush;

	TextRender::pDWriteFactory->CreateTextFormat
	(
		UI_MenuOption::TEXT_FONT_DEFAULT,
		NULL,
		fontWeight,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		textSize,
		L"en-us",
		&pTextFormat
	);
	pTextFormat->SetTextAlignment(textAlignHorizontal);
	pTextFormat->SetParagraphAlignment(textAlignVertical);
	pRT->CreateSolidColorBrush
	(
		(highlighted) ? UI_MenuOption::TEXT_COLOR_HIGHLIGHTED : UI_MenuOption::TEXT_COLOR_DEFAULT,
		&pBrush
	);

	pRT->DrawTextA(text.c_str(), text.length(), pTextFormat, bounds, pBrush);

	pBrush->Release();
	pTextFormat->Release();
}

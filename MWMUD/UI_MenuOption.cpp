#include "UI_MenuOption.h"

const D2D1::ColorF UI_MenuOption::TEXT_COLOR_HIGHLIGHTED = D2D1::ColorF(D2D1::ColorF::Yellow);

bool UI_MenuOption::hasFocus() { return focused; }

void UI_MenuOption::setFocus(bool focused)
{
	this->focused = focused;
}

//void UI_MenuOption::setCallback(callback onSelect)
void UI_MenuOption::setCallback(std::function<void()> onSelect)
{
	this->onSelect = onSelect;
}

void UI_MenuOption::select()
{
	onSelect();
}

void UI_MenuOption::draw(ID2D1HwndRenderTarget* pRT)
{
	IDWriteTextFormat* pTextFormat;
	ID2D1SolidColorBrush* pBrush;

	HRESULT result = TextRender::pDWriteFactory->CreateTextFormat
	(
		UI_Text::TEXT_FONT_DEFAULT.c_str(),
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
		(focused) ? UI_MenuOption::TEXT_COLOR_HIGHLIGHTED : UI_MenuOption::TEXT_COLOR_DEFAULT,
		&pBrush
	);
	pRT->DrawTextA(text.c_str(), text.length(), pTextFormat, bounds, pBrush);

	pBrush->Release();
	pTextFormat->Release();
}

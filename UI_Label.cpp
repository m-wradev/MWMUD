#include "UI_Label.h"

const D2D1::ColorF UI_Label::TEXT_COLOR_DEFAULT = D2D1::ColorF(D2D1::ColorF::White);
const wchar_t* UI_Label::TEXT_FONT_DEFAULT = L"Gabriola";

void UI_Label::setText(std::wstring text, float textSize,
	DWRITE_TEXT_ALIGNMENT textAlignHorizontal, 
	DWRITE_PARAGRAPH_ALIGNMENT textAlignVertical,
	DWRITE_FONT_WEIGHT fontWeight)
{
	this->text = text;
	this->textSize = textSize;
	this->textAlignHorizontal = textAlignHorizontal;
	this->textAlignVertical = textAlignVertical;
	this->fontWeight = fontWeight;
}

void UI_Label::setBounds(float left, float top, float right, float bottom)
{
	bounds.left = left;
	bounds.top = top;
	bounds.right = right;
	bounds.bottom = bottom;
}

std::wstring UI_Label::getText() const	{ return text; }
D2D1_RECT_F UI_Label::getBounds() const { return bounds; }


void UI_Label::draw(ID2D1HwndRenderTarget* pRT)
{
	IDWriteTextFormat* pTextFormat;
	ID2D1SolidColorBrush* pBrush;

	TextRender::pDWriteFactory->CreateTextFormat
	(
		UI_Label::TEXT_FONT_DEFAULT,
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
	pRT->CreateSolidColorBrush(UI_Label::TEXT_COLOR_DEFAULT, &pBrush);

	pRT->DrawTextA(text.c_str(), text.length(), pTextFormat, bounds, pBrush);
	
	pBrush->Release();
	pTextFormat->Release();
}
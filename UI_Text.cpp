#include "UI_Text.h"

const D2D1::ColorF UI_Text::TEXT_COLOR_DEFAULT = D2D1::ColorF(D2D1::ColorF::White);
const wchar_t* UI_Text::TEXT_FONT_DEFAULT = L"Arial";

void UI_Text::setText(std::wstring text, float textSize,
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

void UI_Text::setBounds(float left, float top, float right, float bottom)
{
	bounds.left = left;
	bounds.top = top;
	bounds.right = right;
	bounds.bottom = bottom;
}

const std::wstring UI_Text::getText()	{ return text; }
const D2D1_RECT_F UI_Text::getBounds()	{ return bounds; }

const float UI_Text::getTextHeight()
{
	HRESULT result;

	IDWriteTextFormat* pTextFormat;
	result = TextRender::pDWriteFactory->CreateTextFormat
	(
		UI_Text::TEXT_FONT_DEFAULT,
		NULL,
		fontWeight,
		//DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		textSize,
		L"en-us",
		&pTextFormat
	);

	IDWriteTextLayout* pTextLayout;
	result = TextRender::pDWriteFactory->CreateTextLayout
	(
		text.c_str(),
		text.length(),
		pTextFormat,
		bounds.right - bounds.left,
		MAXINT,	// no height restraint
		&pTextLayout
	);

	DWRITE_TEXT_METRICS metrics;
	pTextLayout->GetMetrics(&metrics);
	pTextLayout->Release();

	return metrics.height;
}

void UI_Text::draw(ID2D1HwndRenderTarget* pRT)
{
	IDWriteTextFormat* pTextFormat;
	ID2D1SolidColorBrush* pBrush;

	TextRender::pDWriteFactory->CreateTextFormat
	(
		UI_Text::TEXT_FONT_DEFAULT,
		nullptr,
		fontWeight,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		textSize,
		L"en-us",
		&pTextFormat
	);

	pTextFormat->SetTextAlignment(textAlignHorizontal);
	pTextFormat->SetParagraphAlignment(textAlignVertical);
	pRT->CreateSolidColorBrush(UI_Text::TEXT_COLOR_DEFAULT, &pBrush);
	pRT->DrawTextA(text.c_str(), text.length(), pTextFormat, bounds, pBrush);
	
	pBrush->Release();
	pTextFormat->Release();
}
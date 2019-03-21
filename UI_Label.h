#pragma once
#include "UI_Element.h"

#include <string>

class UI_Label : public UI_Element
{
protected:
	//std::string text;	// text to be displayed in the label
	/*
	int textSize;		// size of the label text's font
	UINT textAlign;		// alignment of the label's text
	UINT fontWeight;	// weight of the text (i.e. bold, light, etc.)
	*/
	std::wstring text;								// text to display
	float textSize;									// size of the text
	DWRITE_TEXT_ALIGNMENT textAlignHorizontal;		// horizontal alignment of the label's text
	DWRITE_PARAGRAPH_ALIGNMENT textAlignVertical;	// vertical alignment of the label's text
	DWRITE_FONT_WEIGHT fontWeight;					// weight of the text (i.e. bold, light, etc.)
	//RECT bounds;									// bounds of the label
	D2D1_RECT_F bounds;								// bounds of the label

public:
	//static const COLORREF TEXT_COLOR_DEFAULT;
	static const D2D1::ColorF TEXT_COLOR_DEFAULT;
	static const wchar_t* TEXT_FONT_DEFAULT;

	//void setText(std::string text, int textSize, UINT textAlign, UINT fontWeight);
	void setText(std::wstring text, float textSize,
		DWRITE_TEXT_ALIGNMENT textAlignHorizontal, 
		DWRITE_PARAGRAPH_ALIGNMENT textAlignVertical,
		DWRITE_FONT_WEIGHT fontWeight);
	void setBounds(float left, float top, float right, float bottom);

	std::wstring getText() const;
	//RECT getBounds() const;
	D2D1_RECT_F getBounds() const;

	virtual void draw(ID2D1HwndRenderTarget* pRT) override;
};


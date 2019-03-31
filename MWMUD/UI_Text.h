#pragma once
#include <string>

#include "UI_Element.h"

class UI_Text : public UI_Element
{
protected:
	std::wstring text;								// text to display
	float textSize;									// size of the text
	DWRITE_TEXT_ALIGNMENT textAlignHorizontal;		// horizontal alignment of the text in its bounds
	DWRITE_PARAGRAPH_ALIGNMENT textAlignVertical;	// vertical alignment of the text in its bounds
	DWRITE_FONT_WEIGHT fontWeight;					// weight of the text (i.e. bold, light, etc.)
	D2D1_RECT_F bounds;								// bounds of the text area

public:
	virtual ~UI_Text() {}

	static const D2D1::ColorF TEXT_COLOR_DEFAULT;
	static const std::wstring TEXT_FONT_DEFAULT;

	void setText(std::wstring text, float textSize,
		DWRITE_TEXT_ALIGNMENT textAlignHorizontal, 
		DWRITE_PARAGRAPH_ALIGNMENT textAlignVertical,
		DWRITE_FONT_WEIGHT fontWeight);
	void changeText(std::wstring text);
	void setBounds(float left, float top, float right, float bottom);

	// Returns the height of the text
	// Height of text is dependent on the text format and the bounds
	const float getTextHeight();
	const std::wstring getText();
	const D2D1_RECT_F getBounds();

	virtual void draw(ID2D1HwndRenderTarget* pRT) override;
};


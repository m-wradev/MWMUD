#pragma once
#include "UI_Element.h"

#include <string>

class UI_Label : public UI_Element
{
protected:
	std::string text;	// text to be displayed in the label
	int textSize;		// size of the label text's font
	UINT textAlign;		// alignment of the label's text
	UINT fontWeight;	// weight of the text (i.e. bold, light, etc.)
	RECT bounds;		// bounds of the label

public:
	static const COLORREF TEXT_COLOR_DEFAULT = RGB(255, 255, 255);

	void setText(std::string text, int textSize, UINT textAlign, UINT fontWeight);
	void setBounds(int left, int top, int right, int bottom);

	std::string getText() const;
	RECT getBounds() const;

	virtual void draw(HWND) override;
};


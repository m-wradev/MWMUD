#pragma once
#include "UI_Element.h"
#include "UI_Text.h"

#include <type_traits>
#include <list>

template <typename T>
class UI_VerticalList : public UI_Element
{
	static_assert(std::is_base_of<UI_Text, T>::value, "T must inherit from UI_Text.");

private:
	std::list<T> elements;

	int fontSize;									// font size of each element 
	DWRITE_FONT_WEIGHT fontWeight;					// weight of text font
	DWRITE_TEXT_ALIGNMENT textAlignHorizontal;		// text's horizontal alignment
	DWRITE_PARAGRAPH_ALIGNMENT textAlignVertical;	// text's vertical alignment
	int elementOffset;								// offset of each element vertically from each other
	int top;										// y coord of top-left corner
	int left;										// x coord of top-left corner
	int right;										// x coord of right side

public:
	void set(int fontSize, 
		DWRITE_TEXT_ALIGNMENT textAlignHorizontal,
		DWRITE_PARAGRAPH_ALIGNMENT textAlignVertical,
		DWRITE_FONT_WEIGHT fontWeight,
		int elementOffset, int left, int top, int right)
	{
		this->fontSize = fontSize;
		this->fontWeight = fontWeight;
		this->textAlignHorizontal = textAlignHorizontal;
		this->textAlignVertical = textAlignVertical;
		this->elementOffset = elementOffset;
		this->left = left;
		this->top = top;
		this->right = right;
	}

	std::list<T>* getElements() { return &elements; }

	// Add an element to the container.
	// Returns the inserted element for the user to perform further operations on.
	T& addElement(std::wstring text)
	{
		T t;
		t.setText(text, fontSize, textAlignHorizontal, textAlignVertical, fontWeight);
		t.setBounds(left, top, right, MAXINT);	// init bounds to size of this container (don't care about bottom)
		
		float textHeight = t.getTextHeight();
		if (elements.size() < 1) // element is first one added, so it goes at the top
		{
			t.setBounds(left, top, right, top + textHeight + elementOffset);
		}
		else // top of element should be the bottom of the previous element in the list
		{
			t.setBounds(left, elements.back().getBounds().bottom,
				right, elements.back().getBounds().bottom + textHeight + elementOffset);
		}

		elements.push_back(t);
		return elements.back();
	}

	void draw(ID2D1HwndRenderTarget* pRT) override
	{
		for (T e : elements)
			e.draw(pRT);
	}
};
#pragma once

#include <type_traits>
#include <list>

#include "UI_Element.h"
#include "UI_Text.h"

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

	// Reposition the UI elements so that they stack nicely on screen.
	// Calculated from top down.
	void repositionElements()
	{
		float height = 0;
		for (T& e : elements)
		{
			float tHeight = e.getTextHeight();
			e.setBounds(left, top + height, right, top + height + tHeight);

			height += tHeight + elementOffset;
		}
	}

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
	int getElementOffset() { return elementOffset; }

	float getHeight()
	{
		float height = 0.0f;
		for (T& e : elements)
			height += e.getTextHeight() + elementOffset;

		//height -= elementOffset; // strip away offset from last element

		return height;
	}

	// Add an element to the container.
	// Returns the inserted element for the user to perform further operations on.
	T& push_back(std::wstring text)
	{
		T t;
		t.setText(text, fontSize, textAlignHorizontal, textAlignVertical, fontWeight);
		t.setBounds(left, top, right, INT_MAX);	// init bounds to size of this container (don't care about bottom)
		
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

	// Add a string to the top of the UI list
	// push a string to the front of the logical list
	T& push_front(std::wstring text)
	{
		T t;
		t.setText(text, fontSize, textAlignHorizontal, textAlignVertical, fontWeight);
		t.setBounds(left, top, right, INT_MAX);

		float textHeight = t.getTextHeight();
		t.setBounds(left, top, right, textHeight);

		elements.push_front(t);
		repositionElements();

		return elements.front();
	}

	// remove the element at the front of the list
	void pop_front()
	{
		elements.pop_front();
		repositionElements();
	}

	void pop_back()
	{
		elements.pop_back();
	}

	// Clear the list
	void clear()
	{
		elements.clear();
	}

	void draw(ID2D1HwndRenderTarget* pRT) override
	{
		for (T e : elements)
			e.draw(pRT);
	}
};
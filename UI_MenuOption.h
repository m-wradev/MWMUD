#pragma once
#include <Windows.h>
#include <string>
#include <functional>

class UI_MenuOption
{
private:
	static const COLORREF COLOR_DEFAULT= RGB(255, 255, 255);
	static const COLORREF COLOR_HIGHLIGHTED = RGB(255, 255, 0);

	std::string labelText;
	int labelFontSize;
	UINT labelFontAlignment;

	RECT bounds;			// boundaries of the UI element
	bool highlighted;		// whether the option is currently highlighted
	
public:
	UI_MenuOption();
	UI_MenuOption(std::string labelText, int labelFontSize, int labelFontAlignment, bool highlighted = false);
	~UI_MenuOption();

	// set all variables
	void set(std::string labelText, int labelFontSize, UINT labelFontAlignment, 
			 int left, int top, int right, int bottom, bool highlighted = false);

	// set the bounds
	void setBounds(int left, int top, int right, int bottom);

	// set as highlighted
	void setHighlighted(bool highlighted);

	std::string getLabelText() const;
	RECT getBounds() const;

	// select the menu option and execute the function given to it
	// void select();

	// draw the screen
	void draw(HWND hWnd);
};


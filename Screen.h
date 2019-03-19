#pragma once

#include <Windows.h>

class Screen
{
private:

protected:

public:
	Screen();
	~Screen();

	// Handle keypresses
	virtual void handleKeypress(char) = 0;

	// Draw the screen
	virtual void draw(HWND) = 0;
};

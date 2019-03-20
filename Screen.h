#ifndef SCREEN_H
#define SCREEN_H

#include <Windows.h>

class Screen
{
protected:
public:
	// Handle keypresses
	virtual void handleKeypress(char) = 0;

	// Draw the screen
	virtual void draw(HWND) = 0;
};

#endif

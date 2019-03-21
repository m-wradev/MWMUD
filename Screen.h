#ifndef SCREEN_H
#define SCREEN_H

#include <d2d1.h>
#pragma comment(lib, "d2d1.lib")

class Screen
{
protected:
public:
	// Handle keypresses
	virtual void handleKeypress(char) = 0;

	// Draw the screen
	virtual void draw(ID2D1HwndRenderTarget* pRT) = 0;
};

#endif

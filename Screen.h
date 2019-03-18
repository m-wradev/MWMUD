#pragma once

#include <Windows.h>

class Screen
{
private:

protected:

public:
	Screen();
	~Screen();

	// Draw the screen
	virtual void draw(HWND) = 0;
};

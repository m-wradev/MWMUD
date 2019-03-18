#pragma once

#include <Windows.h>

class Screen
{
private:
	UI_Layout ui;

public:
	Screen();
	~Screen();

	// Draw the screen
	void Draw(HWND);
};


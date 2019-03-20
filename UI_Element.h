#pragma once
#include <Windows.h>

class UI_Element
{
public:
	virtual void draw(HWND) = 0;
};

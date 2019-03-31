#pragma once

#include <d2d1.h>
#pragma comment(lib, "d2d1.lib")

#include "TextRender.h"

class UI_Element
{
public:
	virtual ~UI_Element() {}
	virtual void draw(ID2D1HwndRenderTarget* pRT) = 0;
};

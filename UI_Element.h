#pragma once
#include "TextRender.h"

#include <d2d1.h>
#pragma comment(lib, "d2d1.lib")

class UI_Element
{
public:
	virtual void draw(ID2D1HwndRenderTarget* pRT) = 0;
};

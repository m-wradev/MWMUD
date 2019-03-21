#pragma once
#include "UI_Element.h"

class UI_ChatIO : public UI_Element
{
private:


public:
	UI_ChatIO();
	~UI_ChatIO();

	void draw(ID2D1HwndRenderTarget* pRT) override;
};


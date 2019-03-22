#include "UI_Chatbox.h"

void UI_Chatbox::setBounds(float left, float top, float right, float bottom)
{
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;
}

void UI_Chatbox::onNotify(GameEvent* evt)
{
}

void UI_Chatbox::draw(ID2D1HwndRenderTarget* pRT)
{
	chatOutput.draw(pRT);
	chatInput.draw(pRT);
}
#include "GameScreen.h"

#include "Dispatcher.h"
#include "GameEvent.h"

GameScreen::GameScreen()
{
	textOut.set(14, DWRITE_TEXT_ALIGNMENT_LEADING, DWRITE_PARAGRAPH_ALIGNMENT_CENTER,
		DWRITE_FONT_WEIGHT_NORMAL, 5, 0, 0, 200);
	textOut.addElement(L"Label 01");
	textOut.addElement(L"Label 02");
	textOut.addElement(L"Label 03");
	textOut.addElement(L"Here is a pretty long label right here. Hopefully it wraps around once it hits the edge of its container.");
	textOut.addElement(L"Label 05");

	textIn.setText(L"", 14, DWRITE_FONT_WEIGHT_NORMAL);
	textIn.setBounds(540 / 2 - 50, 540 / 2 + 50, 960 / 8);
	textIn.setFocused(true);
}

void GameScreen::handleKeypress(wchar_t key)
{
	if (key == VK_ESCAPE)
	{
		Dispatcher::notify(new GameEvent(EVENT_TYPE::GEVT_ENGINE_SHUTDOWN));
	}
}

void GameScreen::draw(ID2D1HwndRenderTarget* pRT)
{
	textOut.draw(pRT);
	textIn.draw(pRT);
}


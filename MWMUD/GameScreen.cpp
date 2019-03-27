#include "GameScreen.h"

#include "Dispatcher.h"
#include "GameEvent.h"

GameScreen::GameScreen()
{
	chatbox.set
	(
		// input box
		14,
		DWRITE_TEXT_ALIGNMENT_LEADING,
		DWRITE_PARAGRAPH_ALIGNMENT_FAR,
		DWRITE_FONT_WEIGHT_NORMAL,

		// output box
		14,
		DWRITE_TEXT_ALIGNMENT_LEADING,
		DWRITE_PARAGRAPH_ALIGNMENT_CENTER, // might need to change this value
		DWRITE_FONT_WEIGHT_NORMAL,
		0, 0, 960 / 4, 540 / 4
	);

	chatbox.getInputComponent().setFocused(true);
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
	/*
	textOut.draw(pRT);
	textIn.draw(pRT);
	*/
	chatbox.draw(pRT);
}


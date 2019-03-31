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
		//0, 0, 960 / 4, 540 / 4
		0, 0, 960, 540
	);

	chatbox.setFocus(true);
}

void GameScreen::handleKeypress(wchar_t key)
{
	if (key == VK_ESCAPE)
	{
		Dispatcher::notify(&GameEvent(EVENT_TYPE::GEVT_ENGINE_SHUTDOWN));
	}
	else if (key == VK_RETURN || key == VK_BACK || (key >= ' ' && key <= '~'))
	{
		if (chatbox.hasFocus()) chatbox.handleCharInput(key);
	}
}

void GameScreen::draw(ID2D1HwndRenderTarget* pRT)
{
	chatbox.draw(pRT);
}


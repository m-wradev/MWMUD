#include "TitleScreen.h"

#include "MainMenuScreen.h"
#include "Dispatcher.h"
#include "GameMessage.h"

TitleScreen::TitleScreen()
{
	title.setText(L"MWMUD", 64, DWRITE_TEXT_ALIGNMENT_CENTER, 
		DWRITE_PARAGRAPH_ALIGNMENT_CENTER, DWRITE_FONT_WEIGHT_BOLD);
	title.setBounds(0, 0, 960, 100);

	version.setText(L"Prealpha Version", 16, DWRITE_TEXT_ALIGNMENT_CENTER,
		DWRITE_PARAGRAPH_ALIGNMENT_CENTER, DWRITE_FONT_WEIGHT_LIGHT);
	version.setBounds(0, 90, 960, 110);

	prompt.setText(L"Press ENTER", 24, DWRITE_TEXT_ALIGNMENT_CENTER,
		DWRITE_PARAGRAPH_ALIGNMENT_CENTER, DWRITE_FONT_WEIGHT_NORMAL);
	prompt.setBounds(0, 540 / 2 + 20, 960, 540 / 2 - 20);
}

// handle keypresses
void TitleScreen::handleKeypress(char keycode)
{
	if (keycode == VK_RETURN)
	{
		Dispatcher::notify(new ScreenMessage(MessageType::GMSG_SCREEN_ADVANCE, new MainMenuScreen()));
	}
}

void TitleScreen::draw(ID2D1HwndRenderTarget* pRT)
{
	title.draw(pRT);
	version.draw(pRT);
	prompt.draw(pRT);
}

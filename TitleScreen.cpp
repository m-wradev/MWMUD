#include "TitleScreen.h"

#include "MainMenuScreen.h"
#include "Dispatcher.h"
#include "GameMessage.h"

TitleScreen::TitleScreen()
{
	title.setText("MWMUD", 64, DT_SINGLELINE | DT_BOTTOM | DT_CENTER, FW_BOLD);
	title.setBounds(0, 0, 960, 100);

	version.setText("Prealpha Version", 14, DT_SINGLELINE | DT_TOP | DT_CENTER, FW_LIGHT);
	version.setBounds(0, 100, 960, 120);

	prompt.setText("Press ENTER", 24, DT_SINGLELINE | DT_CENTER | DT_VCENTER, FW_DEMIBOLD);
	prompt.setBounds(0, 540 / 2 + 20, 960, 540 / 2 - 20);
}

void TitleScreen::handleKeypress(char keycode)
{
	if (keycode == VK_RETURN)
	{
		Dispatcher::notify
		(
			new ScreenMessage(MessageType::GMSG_SCREEN_ADVANCE, new MainMenuScreen())
		);
	}
}

void TitleScreen::draw(HWND hWnd)
{
	title.draw(hWnd);
	version.draw(hWnd);
	prompt.draw(hWnd);
}

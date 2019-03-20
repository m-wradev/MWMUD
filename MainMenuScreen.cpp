#include "MainMenuScreen.h"

#include "TitleScreen.h"

#include "Dispatcher.h"
#include "GameMessage.h"

MainMenuScreen::MainMenuScreen()
{
	titleLabel.setText("MWMUD", 64, DT_SINGLELINE | DT_VCENTER | DT_CENTER, FW_BOLD);
	titleLabel.setBounds(0, 0, 960, 100);

	menuOptions.set(24, DT_SINGLELINE | DT_VCENTER | DT_CENTER, 24, 0, 540 / 2, 960);
	menuOptions.addOption("Play", 
		[]() { Dispatcher::notify(new ScreenMessage(MessageType::GMSG_SCREEN_CLEARANDSET, new TitleScreen())); });
	menuOptions.addOption("Options",
		[]() { Dispatcher::notify(new ScreenMessage(MessageType::GMSG_SCREEN_ADVANCE, nullptr)); });
	menuOptions.addOption("Exit",
		[]() { Dispatcher::notify(new ScreenMessage(MessageType::GMSG_UNKNOWN, nullptr)); });

	highlightedOption = menuOptions.getOptions()->begin();
	highlightedOption->setHighlighted(true);
}

void MainMenuScreen::handleKeypress(char keycode)
{
	if		(keycode == VK_RETURN)
	{
		highlightedOption->select();
	}
	else if (keycode == VK_ESCAPE)
	{
		Dispatcher::notify(new ScreenMessage(MessageType::GMSG_SCREEN_RETURN));
	}
	else if (keycode == VK_UP)
	{
		// perform validation to ensure that we're not going to move behind the beginning of the list
		if (highlightedOption != menuOptions.getOptions()->begin())
		{
			highlightedOption->setHighlighted(false);
			highlightedOption--;
			highlightedOption->setHighlighted(true);
		}
	}
	else if (keycode == VK_DOWN)
	{
		// perform validation to ensure that we're not going to dereference end of list
		if (highlightedOption != --menuOptions.getOptions()->end())
		{
			highlightedOption->setHighlighted(false);
			highlightedOption++;
			highlightedOption->setHighlighted(true);
		}
	}
}

void MainMenuScreen::draw(HWND hWnd)
{
	titleLabel.draw(hWnd);
	menuOptions.draw(hWnd);
}

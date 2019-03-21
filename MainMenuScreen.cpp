#include "MainMenuScreen.h"

#include "TitleScreen.h"

#include "Dispatcher.h"
#include "GameMessage.h"

MainMenuScreen::MainMenuScreen()
{
	titleLabel.setText(L"MWMUD", 64, DWRITE_TEXT_ALIGNMENT_CENTER,
		DWRITE_PARAGRAPH_ALIGNMENT_CENTER, DWRITE_FONT_WEIGHT_BOLD);
	titleLabel.setBounds(0, 0, 960, 100);

	versionLabel.setText(L"Prealpha Version", 16, DWRITE_TEXT_ALIGNMENT_CENTER,
		DWRITE_PARAGRAPH_ALIGNMENT_CENTER, DWRITE_FONT_WEIGHT_LIGHT);
	versionLabel.setBounds(0, 90, 960, 110);

	menuOptions.set(24, DWRITE_TEXT_ALIGNMENT_CENTER, DWRITE_PARAGRAPH_ALIGNMENT_CENTER,
		32, 0, 200, 960);
	menuOptions.addOption(L"Single Player", 
		[]() { Dispatcher::notify(new ScreenMessage(MessageType::GMSG_SCREEN_CLEARANDSET, nullptr)); });
	menuOptions.addOption(L"Multi Player",
		[]() { Dispatcher::notify(new ScreenMessage(MessageType::GMSG_SCREEN_ADVANCE, nullptr)); });
	menuOptions.addOption(L"Exit",
		[]() { Dispatcher::notify(new GameMessage(MessageType::GMSG_ENGINE_SHUTDOWN)); });

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

void MainMenuScreen::draw(ID2D1HwndRenderTarget* pRT)
{
	titleLabel.draw(pRT);
	versionLabel.draw(pRT);
	menuOptions.draw(pRT);
}

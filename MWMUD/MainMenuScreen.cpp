#include "MainMenuScreen.h"

#include "MPConnectScreen.h"
#include "Dispatcher.h"

MainMenuScreen::MainMenuScreen()
{
	title.setText(L"MWMUD", 64, DWRITE_TEXT_ALIGNMENT_CENTER,
		DWRITE_PARAGRAPH_ALIGNMENT_CENTER, DWRITE_FONT_WEIGHT_BOLD);
	title.setBounds(0, 0, 960, 100);

	version.setText(L"Prealpha Version", 16, DWRITE_TEXT_ALIGNMENT_CENTER,
		DWRITE_PARAGRAPH_ALIGNMENT_CENTER, DWRITE_FONT_WEIGHT_LIGHT);
	version.setBounds(0, 90, 960, 110);

	menuOptions.set(24, DWRITE_TEXT_ALIGNMENT_CENTER, DWRITE_PARAGRAPH_ALIGNMENT_CENTER,
		DWRITE_FONT_WEIGHT_NORMAL, 10, 0, 200, 960);
	menuOptions.push_back(L"Join Game").setCallback
	([]() { Dispatcher::notify(&ScreenEvent(EVENT_TYPE::GEVT_SCREEN_ADVANCE, new MPConnectScreen())); });
	menuOptions.push_back(L"Exit").setCallback
	([]() { Dispatcher::notify(&ScreenEvent(EVENT_TYPE::GEVT_ENGINE_SHUTDOWN)); });

	highlightedOption = menuOptions.getElements()->begin();
	highlightedOption->setFocus(true);
}

void MainMenuScreen::handleKeypress(wchar_t key)
{
	if		(key == VK_RETURN)
	{
		highlightedOption->select();
	}
	else if (key == VK_ESCAPE)
	{
		Dispatcher::notify(&ScreenEvent(EVENT_TYPE::GEVT_SCREEN_RETURN));
	}
	else if (key == VK_UP)
	{
		// perform validation to ensure that we're not going to move behind the beginning of the list
		if (highlightedOption != menuOptions.getElements()->begin())
		{
			highlightedOption->setFocus(false);
			highlightedOption--;
			highlightedOption->setFocus(true);
		}
	}
	else if (key == VK_DOWN)
	{
		// perform validation to ensure that we're not going to dereference end of list
		if (highlightedOption != --menuOptions.getElements()->end())
		{
			highlightedOption->setFocus(false);
			highlightedOption++;
			highlightedOption->setFocus(true);
		}
	}
}

void MainMenuScreen::draw(ID2D1HwndRenderTarget* pRT)
{
	title.draw(pRT);
	version.draw(pRT);
	menuOptions.draw(pRT);
}

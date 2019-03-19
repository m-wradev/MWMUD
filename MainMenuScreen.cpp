#include "MainMenuScreen.h"

MainMenuScreen::MainMenuScreen()
{
	titleRect.left = 0;
	titleRect.top = 0;
	titleRect.right = 960;
	titleRect.bottom = 100;
	titleFont = CreateFont(64, 0, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, "SYSTEM_FIXED_FONT");

	menuOptions.set(24, DT_SINGLELINE | DT_VCENTER | DT_CENTER, 24, 0, 540 / 2, 960);
	menuOptions.addOption("Play");
	menuOptions.addOption("Options");
	menuOptions.addOption("Exit");

	highlightedOption = menuOptions.getOptions()->begin();
	highlightedOption->setHighlighted(true);
}

MainMenuScreen::~MainMenuScreen()
{
	DeleteObject(titleFont);
}

void MainMenuScreen::handleKeypress(char keycode)
{
	if		(keycode == VK_RETURN)
	{
		//highlightedOption->select();
	}
	else if (keycode == VK_UP)
	{
		// perform validation to ensure that we're not going move behind the beginning of the list
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
	menuOptions.draw(hWnd);

	HDC hdc = GetDC(hWnd);
	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, RGB(255, 255, 255));
	SelectObject(hdc, titleFont);
	DrawText(hdc, "MWMUD", -1, &titleRect, DT_SINGLELINE | DT_BOTTOM | DT_CENTER);
}

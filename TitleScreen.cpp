#include "TitleScreen.h"

TitleScreen::TitleScreen()
{
	titleFont = CreateFont(64, 0, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, "SYSTEM_FIXED_FONT");
	versionFont = CreateFont(12, 0, 0, 0, FW_LIGHT, 0, 0, 0, 0, 0, 0, 0, 0, "SYSTEM_FIXED_FONT");
	startPromptFont = CreateFont(24, 0, 0, 0, FW_DEMIBOLD, 0, 0, 0, 0, 0, 0, 0, 0, "SYSTEM_FIXED_FONT");
}

TitleScreen::~TitleScreen()
{
	DeleteObject(startPromptFont);
	DeleteObject(versionFont);
	DeleteObject(titleFont);
}

void TitleScreen::handleKeypress(char keycode)
{
	if (keycode == VK_RETURN)
	{

	}
}

void TitleScreen::draw(HWND hWnd)
{
	// Get the boundaries of the window's drawable area
	RECT cr;
	GetClientRect(hWnd, &cr);

	/* Define the boundaries of the UI elements
	 * TODO: don't hard code the position
	 */
	titleRect.left = 0;
	titleRect.top = 0;
	titleRect.right = cr.right;
	titleRect.bottom = 100;

	versionRect.left = 0;
	versionRect.top = 100;
	versionRect.right = cr.right;
	versionRect.bottom = 110;

	startPromptRect.left = 0;
	startPromptRect.top = 450;
	startPromptRect.right = cr.right;
	startPromptRect.bottom = cr.bottom;

	HDC hdc = GetDC(hWnd);

	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, RGB(255, 255, 255));

	SelectObject(hdc, titleFont);
	DrawText(hdc, "MWMUD", -1, &titleRect, DT_SINGLELINE | DT_BOTTOM | DT_CENTER);

	SelectObject(hdc, versionFont);
	DrawText(hdc, "prealpha version", -1, &versionRect, DT_SINGLELINE | DT_BOTTOM | DT_CENTER);

	SelectObject(hdc, startPromptFont);
	DrawText(hdc, "Press ENTER", -1, &startPromptRect, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
}

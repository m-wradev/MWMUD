#include "MainMenuScreen.h"

MainMenuScreen::MainMenuScreen()
{
	titleFont = CreateFont(64, 0, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, "SYSTEM_FIXED_FONT");
	menuItemsFont = CreateFont(24, 0, 0, 0, FW_LIGHT, 0, 0, 0, 0, 0, 0, 0, 0, "SYSTEM_FIXED_FONT");
}

MainMenuScreen::~MainMenuScreen()
{
	DeleteObject(menuItemsFont);
	DeleteObject(titleFont);
}

void MainMenuScreen::draw(HWND hWnd)
{
	// Get boundaries of window's drawable area
	RECT cr;
	GetClientRect(hWnd, &cr);

	/* Define the boundaries of the UI elements
	 * TODO: don't hard code the position
	 */
	titleRect.left = 0;
	titleRect.top = 0;
	titleRect.right = cr.right;
	titleRect.bottom = 100;

	playRect.left = 0;
	playRect.top = 250;
	playRect.right = cr.right;
	playRect.bottom = 280;

	optionsRect.left = 0;
	optionsRect.top = 280;
	optionsRect.right = cr.right;
	optionsRect.bottom = 310;
	
	exitRect.left = 0;
	exitRect.top = 310;
	exitRect.right = cr.right;
	exitRect.bottom = 340;

	HDC hdc;
	PAINTSTRUCT ps;

	hdc = BeginPaint(hWnd, &ps);
	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, RGB(255, 255, 255));

	SelectObject(hdc, titleFont);
	DrawText(hdc, "MWMUD", -1, &titleRect, DT_SINGLELINE | DT_BOTTOM | DT_CENTER);

	SelectObject(hdc, menuItemsFont);
	DrawText(hdc, "Play Game", -1, &playRect, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
	DrawText(hdc, "Options", -1, &optionsRect, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
	DrawText(hdc, "Exit", -1, &exitRect, DT_SINGLELINE | DT_VCENTER | DT_CENTER);

	EndPaint(hWnd, &ps);
}

/* TODO
 * Dispatch messages to screens so that they can handle events separately
 */
#include <Windows.h>
#include "Game.h"

#include <stack>

#define APPLICATION_NAME "MWMUD"

// 16:9 aspect ratio
#define SCREEN_WIDTH  960
#define SCREEN_HEIGHT 540

//void DrawUI(HWND);

// Globals
//RECT UI_ChatOutputRect;
//RECT UI_ChatInputRect;

//std::string testIn = "";
//std::vector<std::string> testOut;
//std::stack<Screen*> screenStack;	// for screen navigation
Game game;

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance,
				   HINSTANCE prevInstance,
				   LPSTR pCmdLine,
				   int cmdShow)
{
	HWND hWnd;
	WNDCLASSEX wc;
	
	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;		// redraw window when it's moved horizontally or vertically
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszClassName = "WindowClass1";
	RegisterClassEx(&wc);

	// Adjust the size so that the drawable area within the window is our desired resolution
	RECT wr = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
	AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, false);

	// create the window
	hWnd = CreateWindowEx
	(
		NULL,
		"WindowClass1",
		APPLICATION_NAME,
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		300,
		300,
		wr.right - wr.left, // window width
		wr.bottom - wr.top, // window height
		NULL,
		NULL,
		hInstance,
		NULL
	);
	ShowWindow(hWnd, cmdShow);

	// Create the title screen as the first screen on the screen stack
	//screenStack.push(new MainMenuScreen());

	// Application main loop
	MSG msg;
	while (true)
	{
		// check for messages
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			// check for quit message
			if (msg.message == WM_QUIT)
				break;
		}
	}

	return msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		// application quitting
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
		
		// at the beginning of each frame, clear window background to black
		case WM_ERASEBKGND:
		{
			SetClassLongPtr(hWnd, GCLP_HBRBACKGROUND, (long)CreateSolidBrush(RGB(0, 0, 0)));
			break;
		}

		// Each frame, draw the screen
		case WM_PAINT:
		{
			HDC hdc;
			PAINTSTRUCT ps;

			hdc = BeginPaint(hWnd, &ps);
			//screenStack.top()->draw(hWnd);
			game.render(hWnd);
			EndPaint(hWnd, &ps);

			break;
		}

		case WM_KEYDOWN:
		case WM_CHAR:
		{
			/*
			// This was for WM_CHAR.
			// It basically let us display text in the input box as it was being typed.

			if (wParam >= 0x20 && wParam <= 0x7E)
			{
				testIn.push_back(wParam);
			}
			else if (wParam == 0x08 && testIn.length() > 0)
			{
				testIn.pop_back();
			}
			*/
			game.getActiveScreen()->handleKeypress((char)wParam);
			InvalidateRect(hWnd, 0, true);
			break;
		}

	}

	// handle messages that we didn't handle
	return DefWindowProc(hWnd, message, wParam, lParam);
}

void DrawUI(HWND hWnd)
{
	/*
	HDC hdc;		// device context
	PAINTSTRUCT ps;

	// Set up rects
	RECT clientRect; GetClientRect(hWnd, &clientRect);

	// Input rect extends from bottom of output rect to bottom of client
	UI_ChatInputRect.left = clientRect.left;
	UI_ChatInputRect.top = clientRect.bottom;
 	UI_ChatInputRect.right = clientRect.right;
	UI_ChatInputRect.bottom = clientRect.bottom;

	// Output rect extends from top of client to the top of the input rect
	UI_ChatOutputRect.left = clientRect.left;
	UI_ChatOutputRect.top = clientRect.top;
	UI_ChatOutputRect.right = clientRect.right;
	UI_ChatOutputRect.bottom = clientRect.bottom;

	hdc = BeginPaint(hWnd, &ps);

	// Calculate how large the input rectangle should be depending on the height of the would-be drawn text
	// The input rect will only extend as far as the currently drawn text, except in the case where
	// a line break occurs. In this case, the rect should extend to the end of the screen to avoid
	// a situation where a rect containing two lines doesn't reach the right side of the window.
	int inputTextSize = DrawText(hdc, testIn.c_str(), -1, &UI_ChatInputRect, DT_CALCRECT | DT_WORDBREAK);
	UI_ChatInputRect.top -= inputTextSize;	// increase the size of the input rect by the text height.
	UI_ChatOutputRect.bottom = UI_ChatInputRect.top - 1; // bottom of output should be 1 less than top of input to avoid overlap
	if (inputTextSize >= 32)	// text is now larger than one line
		UI_ChatInputRect.right = clientRect.right;	// force input rect to fill screen horizontally

	// Draw input
	SelectObject(hdc, CreateSolidBrush(RGB(60, 60, 60)));
	Rectangle(hdc, UI_ChatInputRect.left, UI_ChatInputRect.top, UI_ChatInputRect.right, UI_ChatInputRect.bottom);

	// Draw text
	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, RGB(200, 200, 200));
	DrawText(hdc, testIn.c_str(), -1, &UI_ChatInputRect, DT_LEFT | DT_WORDBREAK);

	// This is horribly inefficient.
	// Need some way to predict how many messages should be skipped from the beginning of the vector.
	//
	// This calculates the height of the output text.
	// If the height > UI_ChatOutputRect.bottom, then our text is rendering off-screen.
	// So we have to adjust it by not rendering x number of messages at the beginning of the vector.
	int outTextHeight;
	int outMsgStart = 0;
	std::string out;
	do
	{
		out = (outMsgStart > 0) ? "..." : "";

		for (int i = outMsgStart; i < testOut.size(); i++)
		{
			out += (i > 0) ? "\n" + testOut[i] : testOut[i];
		}
		outTextHeight = DrawText(hdc, out.c_str(), -1, &UI_ChatOutputRect, DT_CALCRECT | DT_WORDBREAK);
		UI_ChatOutputRect.bottom = UI_ChatInputRect.top - 1;

		outMsgStart++;
	} 
	while (outTextHeight > UI_ChatOutputRect.bottom);
	DrawText(hdc, out.c_str(), -1, &UI_ChatOutputRect, DT_LEFT | DT_WORDBREAK);

	EndPaint(hWnd, &ps);
	*/
}

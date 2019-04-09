/* TODO
 * Move all Direct2D initializations into the Game class
 */

// debug memory leaks
#ifdef MWMUD_DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

#define _WINSOCKAPI_
#include <Windows.h>
#include <d2d1.h>

#pragma comment(lib, "d2d1")

#include "Game.h"
#include "Dispatcher.h"

#define APPLICATION_NAME "MWMUD"

// 16:9 aspect ratio
#define SCREEN_WIDTH  960
#define SCREEN_HEIGHT 540

// Globals
Game game;
ID2D1Factory* pD2DFactory;
ID2D1HwndRenderTarget* pRT;

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance,
				   HINSTANCE prevInstance,
				   LPSTR pCmdLine,
				   int cmdShow)
{
	// Get memory leak report at each exit point
	#ifdef MWMUD_DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	#endif

	HWND hWnd;
	WNDCLASSEX wc;
	
	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(WNDCLASSEX);
	//wc.style = CS_HREDRAW | CS_VREDRAW;		// redraw window when it's moved horizontally or vertically
	wc.style = NULL;
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

	// Set up Direct2D
	D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pD2DFactory);
	RECT rc; GetClientRect(hWnd, &rc);
	pD2DFactory->CreateHwndRenderTarget
	(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties
		(
			hWnd,
			D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top)
		),
		&pRT
	);

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

		if (!game.isRunning()) break;

		game.render(pRT);
		game.update();
		Sleep(20);
	}

	// Notify the game that we're shutting down so it can properly release resources
	// and shut down subsystems.
	if (game.isRunning())
		Dispatcher::enqueueEvent(new GameEvent(EVENT_TYPE::GEVT_ENGINE_SHUTDOWN));

	pRT->Release();
	pD2DFactory->Release();

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
		
		// Handling keydown and char separately because of a case where
		// VK_RETURN also is sent as a char, making the program read it as
		// two consecutive presses
		case WM_KEYDOWN:
		{
			// Handle arrow keys
			if (wParam >= VK_LEFT && wParam <= VK_DOWN)
				Dispatcher::enqueueEvent (new InputEvent(EVENT_TYPE::GEVT_INPUT_KEYPRESSED, wParam));
			break;
		}

		case WM_CHAR:
		{
			Dispatcher::enqueueEvent (new InputEvent(EVENT_TYPE::GEVT_INPUT_KEYPRESSED, wParam));
			break;
		}
	}

	// handle messages that we didn't handle
	return DefWindowProc(hWnd, message, wParam, lParam);
}

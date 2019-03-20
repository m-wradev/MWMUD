#ifndef GAME_H
#define GAME_H

#include "Screen.h"

#include "GameMessage.h"
#include "Dispatcher.h"
#include "Listener.h"

#include <Windows.h>

#include <stack>

class Game : public Listener
{
	std::stack<Screen*> screenStack;

public:
	Game();
	~Game();

	void returnToPreviousScreen();
	void addActiveScreen(Screen *newScreen);
	void clearScreenStack();
	Screen* getActiveScreen();

	void onNotify(GameMessage* msg) override;

	// render the screen at the top of the screen stack
	void render(HWND hWnd);
};

#endif

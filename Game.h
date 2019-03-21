#ifndef GAME_H
#define GAME_H

#include "Screen.h"

#include "GameMessage.h"
#include "Dispatcher.h"
#include "Listener.h"

#include <d2d1.h>
#pragma comment(lib, "d2d1.lib")

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

	// update game logic
	void update();
	// render the screen at the top of the screen stack
	void render(ID2D1HwndRenderTarget* pRT);
};

#endif

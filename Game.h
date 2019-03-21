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
	bool running;
	std::stack<Screen*> screenStack;

	void returnToPreviousScreen();
	void addActiveScreen(Screen *newScreen);
	void clearScreenStack();

public:
	Game();

	bool isRunning();
	Screen* getActiveScreen();

	// Handle events sent by the event system
	void onNotify(GameMessage* msg) override;

	// update game logic
	void update();

	// render the screen at the top of the screen stack
	void render(ID2D1HwndRenderTarget* pRT);

	// shut down the game and its systems
	void shutdown();
};

#endif

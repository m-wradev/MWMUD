#pragma once
#include "ClientNetwork.h"
#include "ServerNetwork.h"

#include <d2d1.h>
#include <stack>

#pragma comment(lib, "d2d1.lib")

#include "Screen.h"
#include "GameEvent.h"
#include "Listener.h"

class Game : virtual public Listener
{
	bool running;
	std::stack<Screen*> screenStack;

	void returnToPreviousScreen();
	void addActiveScreen(Screen *newScreen);
	void clearScreenStack();

	ServerNetwork* server = nullptr;
	ClientNetwork* client = nullptr;

public:
	Game();

	bool isRunning();
	Screen* getActiveScreen();

	// Handle events sent by the event system
	void onNotify(GameEvent* msg) override;

	// update game logic
	void update();

	// render the screen at the top of the screen stack
	void render(ID2D1HwndRenderTarget* pRT);

	// shut down the game and its systems
	void shutdown();
};

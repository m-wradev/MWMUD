// TODO - Make the screen size globally accessible as a constant value so that UI_Element sizes aren't hardcoded.

#include "Game.h"
#include "GlobalChat.h"
#include "TextRender.h"
#include "TitleScreen.h"
#include "MainMenuScreen.h"
#include "GameScreen.h"
#include "Dispatcher.h"
#include "Util.h"

Game::Game()
{
	GlobalChat::init();
	TextRender::init();

	/*
	if (enet_initialize() != 0)
	{
		// exit
		exit(EXIT_FAILURE);
	}
	*/

	// Subscribe to events
	// ENGINE
	Dispatcher::subscribe(EVENT_TYPE::GEVT_ENGINE_SHUTDOWN, this);

	// NETWORK
	Dispatcher::subscribe(EVENT_TYPE::GEVT_NETWORK_CLIENT_ATTEMPTCONNECT, this);
	//Dispatcher::subscribe(EVENT_TYPE::GEVT_NETWORK_CLIENT_CONNECTIONSUCCESS, this);
	//Dispatcher::subscribe(EVENT_TYPE::GEVT_NETWORK_CLIENT_CONNECTIONFAIL, this);

	// INPUT
	Dispatcher::subscribe(EVENT_TYPE::GEVT_INPUT_KEYPRESSED, this);

	// SCREEN
	Dispatcher::subscribe(EVENT_TYPE::GEVT_SCREEN_ADVANCE, this);
	Dispatcher::subscribe(EVENT_TYPE::GEVT_SCREEN_RETURN, this);
	Dispatcher::subscribe(EVENT_TYPE::GEVT_SCREEN_CLEARANDSET, this);

	running = true;

	screenStack.push(new TitleScreen());
}

void Game::update()
{
	if (client != nullptr)
		client->pollEvents();
}

// Render all elements on the top of the screen stack.
 void Game::render(ID2D1HwndRenderTarget* pRT)
{
	 pRT->BeginDraw();

	 pRT->Clear(D2D1::ColorF(D2D1::ColorF::Black));
	 screenStack.top()->draw(pRT);

	 pRT->EndDraw();
}

void Game::shutdown()
{
	Dispatcher::unsubscribe(EVENT_TYPE::GEVT_ENGINE_SHUTDOWN, this);
	Dispatcher::unsubscribe(EVENT_TYPE::GEVT_NETWORK_CLIENT_ATTEMPTCONNECT, this);
	//Dispatcher::unsubscribe(EVENT_TYPE::GEVT_NETWORK_CLIENT_CONNECTIONSUCCESS, this);
	//Dispatcher::unsubscribe(EVENT_TYPE::GEVT_NETWORK_CLIENT_CONNECTIONFAIL, this);
	Dispatcher::unsubscribe(EVENT_TYPE::GEVT_INPUT_KEYPRESSED, this);
	Dispatcher::unsubscribe(EVENT_TYPE::GEVT_SCREEN_CLEARANDSET, this);
	Dispatcher::unsubscribe(EVENT_TYPE::GEVT_SCREEN_RETURN, this);
	Dispatcher::unsubscribe(EVENT_TYPE::GEVT_SCREEN_ADVANCE, this);
	
	TextRender::pDWriteFactory->Release();
	clearScreenStack();

	if (client != nullptr) delete client;
	//enet_deinitialize();

	running = false;
}

// Handle events sent by the event system
void Game::onNotify(GameEvent *evt)
{
	switch (evt->eventType)
	{
		case EVENT_TYPE::GEVT_ENGINE_SHUTDOWN:
		{
			shutdown();
			break;
		};

		case EVENT_TYPE::GEVT_NETWORK_CLIENT_ATTEMPTCONNECT:
		{
			std::wstring ip = static_cast<NetworkEvent*>(evt)->message;

			client = new ClientNetwork();
			if (!client->connectToServer(Util::convert_wstring_to_string(ip)))
			{
				delete client;
				client = nullptr;
			}

			break;
		}

		/*
		case EVENT_TYPE::GEVT_NETWORK_CLIENT_CONNECTIONSUCCESS:
		{
			// If client connected successfully, move to the game screen
			Dispatcher::notify(&ScreenEvent(EVENT_TYPE::GEVT_SCREEN_CLEARANDSET, new GameScreen()));
			break;
		}
		*/

		case EVENT_TYPE::GEVT_INPUT_KEYPRESSED:
		{
			screenStack.top()->handleKeypress(static_cast<InputEvent*>(evt)->key);
			break;
		}

		case EVENT_TYPE::GEVT_SCREEN_ADVANCE:
		{
			addActiveScreen(static_cast<ScreenEvent*>(evt)->nextScreen);
			break;
		}

		case EVENT_TYPE::GEVT_SCREEN_RETURN:
		{
			returnToPreviousScreen();
			break;
		}

		case EVENT_TYPE::GEVT_SCREEN_CLEARANDSET:
		{
			clearScreenStack();
			addActiveScreen(static_cast<ScreenEvent*>(evt)->nextScreen);
			break;
		}
	}
}

bool Game::isRunning()			{ return running; }
Screen* Game::getActiveScreen() { return screenStack.top(); }

 /* PRIVATE METHODS */
// return to the previous screen by popping the top of the screen stack
void Game::returnToPreviousScreen() 
{ 
	delete screenStack.top();
	screenStack.pop(); 
}

// Adds a new screen to the stack.
// Useful for menu navigation where navigation history is important.
void Game::addActiveScreen(Screen* newScreen) 
{ 
	screenStack.push(newScreen); 
}

// Clear all screens from the stack
// This essentially clears "screen history".
// For example, if I were deep in a menu and cleared the screen stack, I could
// no longer return to previous screens.
void Game::clearScreenStack()
{
	while (!screenStack.empty())
	{
		delete screenStack.top();
		screenStack.pop();
	}
}

#include "Game.h"

#include "TextRender.h"

#include "TitleScreen.h"
#include "MainMenuScreen.h"
#include "GameScreen.h"

#include "Dispatcher.h"

Game::Game()
{
	TextRender::init();

	//screenStack.push(new TitleScreen());
	screenStack.push(new GameScreen());

	// Subscribe to events
	// ENGINE
	Dispatcher::subscribe(EVENT_TYPE::GEVT_ENGINE_SHUTDOWN, this);

	// INPUT
	Dispatcher::subscribe(EVENT_TYPE::GEVT_INPUT_KEYPRESSED, this);

	// SCREEN
	Dispatcher::subscribe(EVENT_TYPE::GEVT_SCREEN_ADVANCE, this);
	Dispatcher::subscribe(EVENT_TYPE::GEVT_SCREEN_RETURN, this);
	Dispatcher::subscribe(EVENT_TYPE::GEVT_SCREEN_CLEARANDSET, this);

	running = true;
}

void Game::update()
{

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
	Dispatcher::unsubscribe(EVENT_TYPE::GEVT_SCREEN_CLEARANDSET, this);
	Dispatcher::unsubscribe(EVENT_TYPE::GEVT_SCREEN_RETURN, this);
	Dispatcher::unsubscribe(EVENT_TYPE::GEVT_SCREEN_ADVANCE, this);
	Dispatcher::unsubscribe(EVENT_TYPE::GEVT_ENGINE_SHUTDOWN, this);
	
	TextRender::pDWriteFactory->Release();
	clearScreenStack();

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
		screenStack.pop(); 
}

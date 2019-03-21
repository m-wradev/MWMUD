#include "Game.h"

#include "TextRender.h"

#include "TitleScreen.h"
#include "MainMenuScreen.h"

Game::Game()
{
	TextRender::init();

	screenStack.push(new TitleScreen());

	// Subscribe to events
	Dispatcher::subscribe(MessageType::GMSG_SCREEN_ADVANCE, this);
	Dispatcher::subscribe(MessageType::GMSG_SCREEN_RETURN, this);
	Dispatcher::subscribe(MessageType::GMSG_SCREEN_CLEARANDSET, this);
}

Game::~Game()
{
	while (!screenStack.empty())
	{
		delete screenStack.top();
		screenStack.pop();
	}
}

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
	{ 
		delete screenStack.top(); 
		screenStack.pop(); 
	}
}

// Get the screen on the top of the screen stack
Screen* Game::getActiveScreen() { return screenStack.top(); }

// Handle events sent by the event system
void Game::onNotify(GameMessage *msg)
{
	switch (msg->messageType)
	{
		case MessageType::GMSG_SCREEN_ADVANCE:
		{
			addActiveScreen(static_cast<ScreenMessage*>(msg)->nextScreen);
			break;
		}

		case MessageType::GMSG_SCREEN_RETURN:
		{
			returnToPreviousScreen();
			break;
		}

		case MessageType::GMSG_SCREEN_CLEARANDSET:
		{
			clearScreenStack();
			addActiveScreen(static_cast<ScreenMessage*>(msg)->nextScreen);
			break;
		}
	}
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

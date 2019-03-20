#include "Game.h"

#include "TitleScreen.h"
#include "MainMenuScreen.h"

Game::Game()
{
	screenStack.push(new MainMenuScreen());

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

void Game::returnToPreviousScreen() 
{ 
	screenStack.pop(); 
}

void Game::addActiveScreen(Screen* newScreen) 
{ 
	screenStack.push(newScreen); 
}

void Game::clearScreenStack()
{
	while (!screenStack.empty()) 
	{ 
		delete screenStack.top(); 
		screenStack.pop(); 
	}
}

Screen* Game::getActiveScreen() { return screenStack.top(); }

void Game::onNotify(GameMessage *msg)
{
	switch (msg->messageType)
	{
		case MessageType::GMSG_SCREEN_ADVANCE:
		{
			addActiveScreen(static_cast<ScreenMessage*>(msg)->nextScreen);
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

 void Game::render(HWND hWnd)
{
	screenStack.top()->draw(hWnd);
}

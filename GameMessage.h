#pragma once

#include "Screen.h"

enum class MessageType
{
	GMSG_UNKNOWN = 0,

	/* Messages related to screens (game states)
	 */
	GMSG_SCREEN_ADVANCE,		// add a screen to the screen stack
	GMSG_SCREEN_RETURN,			// go back to the immediate previous screen
	GMSG_SCREEN_CLEARANDSET,	// clear all screens and set a new one
};

struct GameMessage
{
	MessageType messageType;

	GameMessage(MessageType mt)
	{
		messageType = mt;
	}
};

struct ScreenMessage : public GameMessage
{
	Screen *nextScreen;

	ScreenMessage(MessageType mt, Screen *nextScreen = nullptr)
		: GameMessage(mt), nextScreen(nextScreen) {}
};

#pragma once

#include "Screen.h"

#include <string>

enum class EVENT_TYPE
{
	GEVT_UNKNOWN = 0,

	// ENGINE - HIGH PRIORITY NOTIFICATIONS
	GEVT_ENGINE_SHUTDOWN,		// shut down the game

	// INPUT
	GEVT_INPUT_KEYPRESSED,		// user pressed a key on the keyboard

	// SCREENS
	GEVT_SCREEN_ADVANCE,		// add a screen to the screen stack
	GEVT_SCREEN_RETURN,			// go back to the immediate previous screen
	GEVT_SCREEN_CLEARANDSET,	// clear all screens and set a new one

	// GAME CHAT
	GEVT_CHAT_MESSAGE_SENT,		// user sends a message through the chat system
	GEVT_CHAT_MESSAGE_RECEIVED,	// game receives a chat message
};

struct GameEvent
{
	EVENT_TYPE eventType;

	GameEvent(EVENT_TYPE et) : eventType(et) {}
};

struct InputEvent : public GameEvent
{
	wchar_t key;
	InputEvent(EVENT_TYPE et, wchar_t key)
		: GameEvent(et), key(key) {}
};

struct ScreenEvent : public GameEvent
{
	Screen *nextScreen;

	ScreenEvent(EVENT_TYPE et, Screen *nextScreen = nullptr)
		: GameEvent(et), nextScreen(nextScreen) {}
};

struct ChatEvent : public GameEvent
{
	std::wstring message;

	ChatEvent(EVENT_TYPE et, std::wstring message)
		: GameEvent(et), message(message) {}
};

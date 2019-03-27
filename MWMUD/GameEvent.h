#pragma once

#include <string>

#include "Screen.h"
#include "UI_Element.h"

enum class EVENT_TYPE
{
	GEVT_UNKNOWN = 0,

	// ENGINE - HIGH PRIORITY NOTIFICATIONS
	GEVT_ENGINE_SHUTDOWN,		// shut down the game

	// NETWORK EVENTS
	GEVT_NETWORK_SERVER_CREATED,			// user requested that a server be created and hosted on their machine
	GEVT_NETWORK_SERVER_SHUTDOWN,			// server is shutting down
	GEVT_NETWORK_CLIENT_CONNECTED,			// client connected to server
	GEVT_NETWORK_CLIENT_CONNECTIONFAILED,	// client failed to connect to server

	// INPUT
	GEVT_INPUT_KEYPRESSED,		// user pressed a key on the keyboard

	// SCREENS
	GEVT_SCREEN_ADVANCE,		// add a screen to the screen stack
	GEVT_SCREEN_RETURN,			// go back to the immediate previous screen
	GEVT_SCREEN_CLEARANDSET,	// clear all screens and set a new one

	// GAME CHAT
	GEVT_CHAT_MESSAGE_SENT,		// user sends a message through the chat system

	// UI ELEMENTS
		// UI_TextInput
		GEVT_UI_TEXTINPUT_HEIGHTCHANGED, // height of the input bounds changed to fit text
};

struct GameEvent
{
	EVENT_TYPE eventType;

	GameEvent(EVENT_TYPE et) : eventType(et) {}
};

struct NetworkNotificationEvent : public GameEvent
{
	std::wstring msg;

	NetworkNotificationEvent(EVENT_TYPE et, std::wstring msg)
		: GameEvent(et), msg(msg) {}
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

struct UIEvent : public GameEvent
{
	UI_Element* element; // element that sent the update. use this to get the updated values
	std::string info;
	
	UIEvent(EVENT_TYPE et, UI_Element* element, std::string info)
		: GameEvent(et), element(element), info(info) {}
};

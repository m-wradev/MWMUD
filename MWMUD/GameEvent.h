// TODO - Rename some of these events so that there's a clear delineation between network msg send and chat mGEVT_NETWORK_CLIENT_MESSAGESENDsg send
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
	GEVT_NETWORK_CLIENT_ATTEMPTCONNECT,		// client attempts to connect to a server
	GEVT_NETWORK_CLIENT_CONNECTIONSUCCESS,	// client connected to server
	GEVT_NETWORK_CLIENT_CONNECTIONFAIL,		// client failed to connect to server
	GEVT_NETWORK_CLIENT_DATASEND,			// client sends data to server
	GEVT_NETWORK_CLIENT_DATARECEIVE,		// client received data from server

	// INPUT
	GEVT_INPUT_KEYPRESSED,		// user pressed a key on the keyboard

	// SCREENS
	GEVT_SCREEN_ADVANCE,		// add a screen to the screen stack
	GEVT_SCREEN_RETURN,			// go back to the immediate previous screen
	GEVT_SCREEN_CLEARANDSET,	// clear all screens and set a new one

	// GAME CHAT
	//GEVT_CHAT_MESSAGEPARSE,		// user sends a message to the chat system for parsing
	GEVT_CHAT_MESSAGEDISPLAY,	// chat system needs to display a message
	GEVT_CHAT_CLEARCHAT,		// user wants to clear the chat

	// UI ELEMENTS
		// UI_ChatInput
		GEVT_UI_TEXTINPUT_HEIGHTCHANGED, // height of the input bounds changed to fit text
};

struct GameEvent
{
	EVENT_TYPE eventType;

	GameEvent(EVENT_TYPE et) : eventType(et) {}
	virtual ~GameEvent() {}
};

struct NetworkEvent : public GameEvent
{
	std::string message;

	NetworkEvent(EVENT_TYPE et, std::string message)
		: GameEvent(et), message(message) {}

	~NetworkEvent() {}
};

struct InputEvent : public GameEvent
{
	wchar_t key;
	InputEvent(EVENT_TYPE et, wchar_t key)
		: GameEvent(et), key(key) {}

	~InputEvent() {}
};

struct ScreenEvent : public GameEvent
{
	Screen *nextScreen;

	ScreenEvent(EVENT_TYPE et, Screen *nextScreen = nullptr)
		: GameEvent(et), nextScreen(nextScreen) {}

	~ScreenEvent() {}
};

struct ChatEvent : public GameEvent
{
	std::wstring message;

	ChatEvent(EVENT_TYPE et, std::wstring message)
		: GameEvent(et), message(message) {}

	~ChatEvent() {}
};

struct UIEvent : public GameEvent
{
	UI_Element* element; // element that sent the update. use this to get the updated values
	std::string info;

	UIEvent(EVENT_TYPE et, UI_Element* element, std::string info)
		: GameEvent(et), element(element), info(info) {}

	~UIEvent() {}
};

#pragma once

#include "GameEvent.h"
#include "Listener.h"

#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <exception>

class DuplicateSubscriptionException : public std::exception
{
private:
	const char* file;
	int line;
	const char* func;
	const char* info;

public:
	DuplicateSubscriptionException(const char* msg, int line_, 
		const char* file_, const char* func_, const char* info_ = "")
		: std::exception(msg), file(file_), line(line_), func(func_), info(info_)
	{}

	const char* getFile() const { return file; }
	int getLine() const { return line; }
	const char* getInfo() const { return info; }

};

class Dispatcher
{
private:
	static std::unordered_map<EVENT_TYPE, std::unordered_set<Listener*>> subscriptions;
	static std::queue<GameEvent*> eventQueue;

public:
	// Subscribe a listener to a message type
	static void subscribe(EVENT_TYPE et, Listener* listener);
	// Unsubscribe a listener from a message type
	static void unsubscribe(EVENT_TYPE et, Listener* listener);
	// Place an event into the event queue to be delivered on the next flush
	static void enqueueEvent(GameEvent* gevt);
	// Deliver all events in the queue
	static void flushEvents();
	// Notify all subscribers of a given message type
	static void notify(GameEvent* gevt);
};


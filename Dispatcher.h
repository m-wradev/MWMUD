#pragma once

#include "GameEvent.h"
#include "Listener.h"

#include <map>
#include <unordered_set>
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
	static std::map<EVENT_TYPE, std::unordered_set<Listener*>> subscriptions;

public:
	// Subscribe a listener to a message type
	static void subscribe(EVENT_TYPE et, Listener* listener);
	// Unsubscribe a listener from a message type
	static void unsubscribe(EVENT_TYPE et, Listener* listener);
	// Notify all subscribers of a given message type
	static void notify(GameEvent* msg);
};


#include "Dispatcher.h"

#include <queue>

std::map<EVENT_TYPE, std::unordered_set<Listener*>> Dispatcher::subscriptions;

// Subscribe a listener to a message type
void Dispatcher::subscribe(EVENT_TYPE et, Listener* listener)
{
	//try
	//{
	if (!Dispatcher::subscriptions[et].insert(listener).second)
	{
		throw new DuplicateSubscriptionException
		(
			"Duplicate subscription",
			12,
			"Dispatcher.cpp",
			"subscribe(EVENT_TYPE, Listener*)"
		);
	}
	//}
	//catch (DuplicateSubscriptionException& ex)
	//{
	//	Dispatcher::notify(new GameEvent(EVENT_TYPE::GEVT_ENGINE_SHUTDOWN));
	//}
}

// Unsubscribe a listener from a message type
void Dispatcher::unsubscribe(EVENT_TYPE et, Listener* listener)
{
	Dispatcher::subscriptions[et].erase(listener);
}

// Notify all subscribers of a given message type
void Dispatcher::notify(GameEvent* evt)
{
	// push all listeners subscribed to an event into a queue
	// Note: this might get REALLY EXPENSIVE later on
	// Will have to come up with another way later
	std::queue<Listener*> toNotify;
	for (Listener* l : Dispatcher::subscriptions[evt->eventType])
		toNotify.push(l);

	// now notify each listener and pop them off the queue
	// This method prevents us from sending messages to new subscribers to an event
	// while we're still processing the list
	while (!toNotify.empty())
	{
		toNotify.front()->onNotify(evt);
		toNotify.pop();
	}
}

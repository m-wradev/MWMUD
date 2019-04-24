#include "Dispatcher.h"

std::unordered_map<EVENT_TYPE, std::unordered_set<Listener*>> Dispatcher::subscriptions;
std::queue<std::pair<int, std::pair<EVENT_TYPE, Listener*>>> Dispatcher::subscriptionRequests;
bool Dispatcher::subscriptionsLocked = false;
std::queue<Event*> Dispatcher::eventQueue;
std::queue<Event*> Dispatcher::eventQueueOverflow;
bool Dispatcher::eventQueueLocked = false;

void Dispatcher::lockSubscriptions()	{ subscriptionsLocked = true; }
void Dispatcher::unlockSubscriptions()	{ subscriptionsLocked = false; }

void Dispatcher::subscribe(EVENT_TYPE et, Listener* listener)
{
	if (!subscriptionsLocked)
		subscriptions[et].insert(listener);
	else
		subscriptionRequests.push(std::make_pair(1, std::make_pair(et, listener)));
}

void Dispatcher::unsubscribe(EVENT_TYPE et, Listener* listener)
{
	if (!subscriptionsLocked)
		subscriptions[et].erase(listener);
	else
		subscriptionRequests.push(std::make_pair(0, std::make_pair(et, listener)));
}

void Dispatcher::lockEventQueue()	{ eventQueueLocked = true; }
void Dispatcher::unlockEventQueue()	{ eventQueueLocked = false; }

void Dispatcher::enqueueEvent(Event* evt)
{
	if (!eventQueueLocked)
		eventQueue.push(evt);
	else
		eventQueueOverflow.push(evt);
}

void Dispatcher::flushEvents()
{
	lockEventQueue();
	lockSubscriptions();
	while (!eventQueue.empty())
	{
		notify(eventQueue.front());
		delete eventQueue.front();
		eventQueue.pop();
	}
	unlockSubscriptions();
	unlockEventQueue();

	// Push overflown events into eventQueue
	while (!eventQueueOverflow.empty())
	{
		eventQueue.push(eventQueueOverflow.front());
		eventQueueOverflow.pop();
	}

	// Handle subscription requests
	while (!subscriptionRequests.empty())
	{
		auto request = subscriptionRequests.front();
		
		if (request.first)
			subscribe(request.second.first, request.second.second);
		else
			unsubscribe(request.second.first, request.second.second);

		subscriptionRequests.pop();
	}
}

void Dispatcher::notify(Event* evt)
{
	for (Listener* listener : subscriptions[evt->eventType])
		listener->onNotify(evt);
}
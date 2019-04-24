#pragma once

#include "Events.h"
#include "Listener.h"

#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <utility>

class Dispatcher
{
private:
	static std::unordered_map<EVENT_TYPE, std::unordered_set<Listener*>> subscriptions;
	// Listeners that tried to subscribe to event types while eventQueue was being flushed.
	// The first element of the first pair indicates what operation should be performed:
	//		0 - unsubscribe
	//		1 - subscribe
	static std::queue<std::pair<int, std::pair<EVENT_TYPE, Listener*>>> subscriptionRequests;
	// If we're flushing the event queue, we don't want to add new subscriptions since they
	// might receive an event that wasn't intended for them.
	// We'll wait until all events are flushed, then subscribe the listeners to event types.
	static bool subscriptionsLocked;
	static void lockSubscriptions();
	static void unlockSubscriptions();

	static std::queue<Event*> eventQueue;
	// Events that tried to be added while eventQueue was being flushed
	static std::queue<Event*> eventQueueOverflow;
	// If we're flushing the event queue, we don't want new events to be added to it.
	// We'll lock the queue while flushing, and put events into a different queue until
	// all events in eventQueue are flushed.  After that, we'll move events queued during the
	// flush into eventQueue.
	static bool eventQueueLocked;
	static void lockEventQueue();
	static void unlockEventQueue();

	// Notify all subscribers of a given event type
	static void notify(Event* evt);

public:
	// Subscribe a listener to an event type
	static void subscribe(EVENT_TYPE et, Listener* listener);
	// Unsubscribe a listener from an event type
	static void unsubscribe(EVENT_TYPE et, Listener* listener);
	// Place an event into the event queue to be delivered on the next flush
	static void enqueueEvent(Event* evt);
	// Deliver all events in queue to subscribers of the event type
	static void flushEvents();
};
#include "Dispatcher.h"

std::map<MessageType, std::set<Listener*>> Dispatcher::subscriptions;

// Subscribe a listener to a message type
void Dispatcher::subscribe(MessageType mt, Listener* listener)
{
	Dispatcher::subscriptions[mt].insert(listener);
}

// Notify all subscribers of a given message type
void Dispatcher::notify(GameMessage* msg)
{
	for (Listener *l : Dispatcher::subscriptions[msg->messageType])
		l->onNotify(msg);
}

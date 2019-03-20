#include "Dispatcher.h"

std::map<MessageType, std::set<Listener*>> Dispatcher::subscriptions;

void Dispatcher::subscribe(MessageType mt, Listener* listener)
{
	Dispatcher::subscriptions[mt].insert(listener);
}

void Dispatcher::notify(GameMessage* msg)
{
	for (Listener *l : Dispatcher::subscriptions[msg->messageType])
		l->onNotify(msg);
}

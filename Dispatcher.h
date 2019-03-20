#pragma once

#include "GameMessage.h"
#include "Listener.h"

#include <map>
#include <set>

class Dispatcher
{
private:
	static std::map<MessageType, std::set<Listener*>> subscriptions;

public:
	static void subscribe(MessageType mt, Listener* listener);
	static void notify(GameMessage* msg);
};


#pragma once

#include <string>

#include "Client.h"

enum class EVENT_TYPE
{
	UNKNOWN = 0,

	// SERVER EVENTS
	SERVER_SHUTDOWN,			// Server is shutting down
	SERVER_CLIENTDISCONNECT,	// Client is disconnecting from the server
	SERVER_BROADCASTMESSAGE,	// Network is broadcasting a message to all clients
};

struct Event
{
	EVENT_TYPE eventType;

	Event(EVENT_TYPE et) : eventType(et) {}
	virtual ~Event() {}
};

namespace ServerEvent
{
	struct Shutdown : public Event
	{
		Shutdown()
			: Event(EVENT_TYPE::SERVER_SHUTDOWN)
		{}

		~Shutdown() {}
	};

	struct ClientDisconnect : public Event
	{
		Client* client;

		ClientDisconnect(Client* client)
			: Event(EVENT_TYPE::SERVER_CLIENTDISCONNECT),
			client(client) 
		{}

		~ClientDisconnect() {}
	};

	struct BroadcastMessage : public Event
	{	
		std::string msg;

		BroadcastMessage(std::string msg)
			: Event(EVENT_TYPE::SERVER_BROADCASTMESSAGE), 
			msg(msg) 
		{}

		~BroadcastMessage() {}
	};
};
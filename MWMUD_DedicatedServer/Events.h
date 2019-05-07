#pragma once

#include <string>

#include "Client.h"

enum class EVENT_TYPE
{
	UNKNOWN = 0,

	/* SERVER EVENTS
	 */
	// GENERAL
	SERVER_SHUTDOWN,					// Server is shutting down

	// NETWORK
	SERVER_NETWORK_CLIENTDISCONNECT,	// Client is disconnecting from the server

	// MESSAGE
	SERVER_MESSAGE_BROADCAST,			// Server is broadcasting a message to all clients
	SERVER_MESSAGE_DIRECT,				// A message is being sent directly to a client
};

struct Event
{
	EVENT_TYPE eventType;

	Event(EVENT_TYPE et) : eventType(et) {}
	virtual ~Event() {}
};

namespace ServerEvent
{
	namespace Network
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
				: Event(EVENT_TYPE::SERVER_NETWORK_CLIENTDISCONNECT),
				client(client)
			{}

			~ClientDisconnect() {}
		};
	}

	namespace Message
	{
		struct Broadcast : public Event
		{
			std::string msg;

			Broadcast(std::string msg)
				: Event(EVENT_TYPE::SERVER_MESSAGE_BROADCAST),
				msg(msg)
			{}

			~Broadcast() {}
		};

		// Message sent directly from the server to the client.
		struct Direct_S2C : public Event
		{
			Client* recipient;
			std::string msg;

			Direct_S2C(Client* recipient, std::string msg)
				: Event(EVENT_TYPE::SERVER_MESSAGE_DIRECT),
				recipient(recipient), msg(msg)
			{}
		};
	}
};
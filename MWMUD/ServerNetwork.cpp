#include <locale>
#include <codecvt>

#include "ServerNetwork.h"
#include "Dispatcher.h"

ServerNetwork::ServerNetwork()
{
	ENetAddress address;

	// Bind the server to the default local host
	// Can specify host address using enet_address_set_host(&address, "x.x.x.x")
	address.host = ENET_HOST_ANY;
	//enet_address_set_host(&address, "161.45.12.237");
	address.port = 1234;	// bind server to port 1234

	// create the server
	server = enet_host_create
	(
		&address,	// address to bind server host to
		MAX_CONNECTIONS, // allow up to MAX_CONNECTIONS clients
		2,	// allow 2 channels to be used: 0 and 1
		0,	// assume any amount of incoming bandwidth
		0	// assume any amount of outgoing bandwidth
	);

	if (server == nullptr)
	{
		// display message stating that user could not create
		// a server.
		
		// for now we'll just exit, but will want to change this in
		// the future.
		exit(EXIT_FAILURE);
	}

	// subscribe to events
	//Dispatcher::subscribe(EVENT_TYPE::GEVT_CHAT_MESSAGE_SENT, this);
}

ServerNetwork::~ServerNetwork()
{
	enet_host_destroy(server);
	//Dispatcher::unsubscribe(EVENT_TYPE::GEVT_CHAT_MESSAGE_SENT, this);
}

void ServerNetwork::pollEvents()
{
	ENetEvent enetevt;
	
	while (enet_host_service(server, &enetevt, 0) > 0)
	{
		switch (enetevt.type)
		{
			case ENET_EVENT_TYPE_CONNECT:
			{
				// just list that a client connected on the screen
				Dispatcher::notify(new ChatEvent(EVENT_TYPE::GEVT_CHAT_MESSAGE_SENT, L"User connected from " + std::to_wstring(enetevt.peer->address.host)));

				//enetevt.peer->data = "Test Peer";
				clients.insert(enetevt.peer);
				break;
			}

			case ENET_EVENT_TYPE_RECEIVE:
			{
				Dispatcher::notify(new ChatEvent(EVENT_TYPE::GEVT_CHAT_MESSAGE_SENT, L"Received packet from " + std::to_wstring(enetevt.peer->address.host) + L" on channel " + std::to_wstring(enetevt.channelID)));

				// send the packet to each client
				for (ENetPeer* client : clients)
					enet_peer_send(client, 0, enetevt.packet);

				// clean up the packet
				enet_packet_destroy(enetevt.packet);
				break;
			}

			case ENET_EVENT_TYPE_DISCONNECT:
			{
				Dispatcher::notify(new ChatEvent(EVENT_TYPE::GEVT_CHAT_MESSAGE_SENT, L"User " + std::to_wstring(enetevt.peer->address.host) + L" disconnected"));

				// Reset peer data
				//enetevt.peer->data = NULL;
				clients.erase(enetevt.peer);
				break;
			}
		}
	}
}

void ServerNetwork::onNotify(GameEvent* gevt)
{
	/*
	if (gevt->eventType == EVENT_TYPE::GEVT_CHAT_MESSAGE_SENT)
	{
		// convert the chat message from wstring to string
		using convert_type = std::codecvt_utf8<wchar_t>;
		std::wstring_convert<convert_type, wchar_t> converter;
		std::string message = converter.to_bytes(static_cast<ChatEvent*>(gevt)->message);

		// Create a packet
		ENetPacket* packet = enet_packet_create(message.c_str(), strlen(message.c_str()) + 1, ENET_PACKET_FLAG_RELIABLE);

		// send packet to each peer
		for (ENetPeer* client : clients)
			enet_peer_send(client, 0, packet);

		// clean up the packet
		enet_packet_destroy(packet);

		// flush the server
		enet_host_flush(server);
	}
	*/
}
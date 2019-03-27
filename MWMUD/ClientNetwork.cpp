#include <locale>
#include <codecvt>

#include "ClientNetwork.h"
#include "GameScreen.h"
#include "Dispatcher.h"
#include "GameEvent.h"

ClientNetwork::ClientNetwork()
{
	client = enet_host_create
	(
		NULL,	// create a client host
		1,		// only allow 1 outgoing connection
		2,		// allow 2 channels for use: 0 and 1
		0,		// assume any amount of incoming bandwidth
		0		// assume any amount of outgoing bandwidth
	);

	if (client == nullptr)
	{
		// send game error that client failed to be created

		// for now just exit, but will want to change this later
		exit(EXIT_FAILURE);
	}

	// subscribe to events
	Dispatcher::subscribe(EVENT_TYPE::GEVT_CHAT_MESSAGE_SENT, this);
}

ClientNetwork::~ClientNetwork()
{
	enet_host_destroy(client);

	// unsubscribe from events
	Dispatcher::unsubscribe(EVENT_TYPE::GEVT_CHAT_MESSAGE_SENT, this);
}

void ClientNetwork::connectToServer(std::string ip)
{
	ENetAddress address;
	ENetEvent enetevt;

	// connect to server
	enet_address_set_host(&address, ip.c_str());
	address.port = 1234;

	// initiate connection and allocate two channel (0 and 1)
	peer = enet_host_connect(client, &address, 2, 0);

	if (peer == nullptr)
	{
		// send game message saying that connection failed
		exit(EXIT_FAILURE);
	}

	// Wait up to 5 seconds for connection attempt to succeed
	if (enet_host_service(client, &enetevt, 5000) > 0 &&
		enetevt.type == ENET_EVENT_TYPE_CONNECT)
	{
		// Once connected, load in game screen
		Dispatcher::notify(new ScreenEvent(EVENT_TYPE::GEVT_SCREEN_CLEARANDSET, new GameScreen()));
	}
	else
	{
		// Either 5 seconds are up or a disconnect event was received
		// Reset peer in the event 5 seconds had run out without any significant event
		enet_peer_reset(peer);

		// notify game that the client failed to join the server
	}

	// notify the game that the client was able to join the server
}

void ClientNetwork::pollEvents()
{
	ENetEvent enetevt;

	while (enet_host_service(client, &enetevt, 0) > 0)
	{
		switch (enetevt.type)
		{
			case ENET_EVENT_TYPE_RECEIVE:
			{
				Dispatcher::notify(new ChatEvent(EVENT_TYPE::GEVT_CHAT_MESSAGE_SENT, L"Received packet from " + std::to_wstring(enetevt.peer->address.host) + L" on channel " + std::to_wstring(enetevt.channelID)));

				// done with packet, so clean it up
				enet_packet_destroy(enetevt.packet);
				break;
			}
		}
	}
}

void ClientNetwork::onNotify(GameEvent* gevt)
{
	if (gevt->eventType == EVENT_TYPE::GEVT_CHAT_MESSAGE_SENT)
	{
		// convert the chat message from wstring to string
		using convert_type = std::codecvt_utf8<wchar_t>;
		std::wstring_convert<convert_type, wchar_t> converter;
		std::string message = converter.to_bytes(static_cast<ChatEvent*>(gevt)->message);

		// Create a packet
		ENetPacket* packet = enet_packet_create(message.c_str(), strlen(message.c_str()) + 1, ENET_PACKET_FLAG_RELIABLE);

		// send packet to the server
		enet_peer_send(peer, 0, packet);

		// clean up the packet
		//enet_packet_destroy(packet);

		// flush the client
		//enet_host_flush(client);
	}
}

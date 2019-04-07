#include <locale>
#include <codecvt>
#include <iostream>

#include "ClientNetwork.h"
#include "GameScreen.h"
#include "Dispatcher.h"
#include "GameEvent.h"
#include "Util.h"

ClientNetwork::ClientNetwork()
{
	Dispatcher::subscribe(EVENT_TYPE::GEVT_NETWORK_CLIENT_DATASEND, this);
}

ClientNetwork::~ClientNetwork()
{
	socket.disconnect();

	Dispatcher::unsubscribe(EVENT_TYPE::GEVT_NETWORK_CLIENT_DATASEND, this);
}

bool ClientNetwork::connectToServer(std::string ip)
{
	// Attempt connection for 3 seconds.
	sf::Socket::Status status = socket.connect(ip, 25565, sf::seconds(3.0f));
	if (status != sf::Socket::Status::Done)
	{
		Dispatcher::notify(&NetworkEvent(EVENT_TYPE::GEVT_NETWORK_CLIENT_CONNECTIONFAIL, L"Failed to connect. Is the server running?"));
		return false;
	}
	else
	{
		socket.setBlocking(false);
		Dispatcher::notify(&NetworkEvent(EVENT_TYPE::GEVT_NETWORK_CLIENT_CONNECTIONSUCCESS, L""));
	}

	return true;
}

void ClientNetwork::pollEvents()
{
	sf::Packet packet;

	// Check if server sent anything
	if (socket.receive(packet) == sf::Socket::Done)
	{
		std::string msg;
		packet >> msg;
		std::wstring widestr = Util::convert_string_to_wstring(msg);
		Dispatcher::notify(&ChatEvent(EVENT_TYPE::GEVT_CHAT_MESSAGEDISPLAY, widestr));
		//Dispatcher::notify(&NetworkEvent(EVENT_TYPE::GEVT_CHAT_MESSAGEPARSE, widestr));
		//Dispatcher::notify(&NetworkEvent(EVENT_TYPE::GEVT_NETWORK_CLIENT_DATARECEIVE, widestr));
	}
}

void ClientNetwork::onNotify(GameEvent* gevt)
{
	if (gevt->eventType == EVENT_TYPE::GEVT_NETWORK_CLIENT_DATASEND)
	{
		// convert the chat message from wstring to string
		using convert_type = std::codecvt_utf8<wchar_t>;
		std::wstring_convert<convert_type, wchar_t> converter;
		std::string message = converter.to_bytes(static_cast<ChatEvent*>(gevt)->message);

		sf::Packet packet;
		packet << message;
		sf::Socket::Status status;
		status = socket.send(packet);
		std::cout << status << std::endl;
	}
}

/*
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
	Dispatcher::subscribe(EVENT_TYPE::GEVT_NETWORK_CLIENT_DATASEND, this);
}

ClientNetwork::~ClientNetwork()
{
	enet_peer_disconnect(peer, 0);
	enet_host_flush(client);
	enet_host_destroy(client);

	// unsubscribe from events
	Dispatcher::unsubscribe(EVENT_TYPE::GEVT_NETWORK_CLIENT_DATASEND, this);
}

void ClientNetwork::connectToServer(std::string ip)
{
	ENetAddress address;
	ENetEvent enetevt;

	// connect to server
	enet_address_set_host(&address, ip.c_str());
	address.port = 25565;

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
		// Notify game that connection succeeded
		Dispatcher::notify(&NetworkEvent(EVENT_TYPE::GEVT_NETWORK_CLIENT_CONNECTIONSUCCESS, L""));
	}
	else
	{
		// Either 5 seconds are up or a disconnect event was received
		// Reset peer in the event 5 seconds had run out without any significant event
		enet_peer_reset(peer);

		// notify game that the client failed to join the server
		Dispatcher::notify(&NetworkEvent(EVENT_TYPE::GEVT_NETWORK_CLIENT_CONNECTIONFAIL, L"Failed to connect. Is the server running?"));
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
				std::string msg = std::string((char*)enetevt.packet->data, enetevt.packet->dataLength);
				std::wstring widestr = Util::convert_string_to_wstring(msg);
				Dispatcher::notify(&NetworkEvent(EVENT_TYPE::GEVT_CHAT_MESSAGEPARSE, widestr));

				// done with packet, so clean it up
				enet_packet_destroy(enetevt.packet);
				break;
			}
		}
	}
}

void ClientNetwork::onNotify(GameEvent* gevt)
{
	if (gevt->eventType == EVENT_TYPE::GEVT_NETWORK_CLIENT_DATASEND)
	{
		// convert the chat message from wstring to string
		using convert_type = std::codecvt_utf8<wchar_t>;
		std::wstring_convert<convert_type, wchar_t> converter;
		std::string message = converter.to_bytes(static_cast<ChatEvent*>(gevt)->message);

		// Create a packet
		ENetPacket* packet = enet_packet_create(message.c_str(), strlen(message.c_str()) + 1, ENET_PACKET_FLAG_RELIABLE);

		// send packet to the server
		enet_peer_send(peer, 0, packet);
		enet_host_flush(client);
		enet_packet_destroy(packet);
	}
	else if (gevt->eventType == EVENT_TYPE::GEVT_NETWORK_CLIENT_DATARECEIVE)
	{

	}
}
*/

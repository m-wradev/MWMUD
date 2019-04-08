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
		Dispatcher::notify(&NetworkEvent(EVENT_TYPE::GEVT_NETWORK_CLIENT_CONNECTIONFAIL, "Failed to connect. Is the server running?"));
		return false;
	}
	else
	{
		socket.setBlocking(false);
		Dispatcher::notify(&NetworkEvent(EVENT_TYPE::GEVT_NETWORK_CLIENT_CONNECTIONSUCCESS, ""));
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
	}
}

void ClientNetwork::onNotify(GameEvent* gevt)
{
	if (gevt->eventType == EVENT_TYPE::GEVT_NETWORK_CLIENT_DATASEND)
	{
		// convert the chat message from wstring to string
		/*
		using convert_type = std::codecvt_utf8<wchar_t>;
		std::wstring_convert<convert_type, wchar_t> converter;
		std::string message = converter.to_bytes(static_cast<ChatEvent*>(gevt)->message);
		*/

		sf::Packet packet;
		packet << static_cast<NetworkEvent*>(gevt)->message;
		sf::Socket::Status status;
		status = socket.send(packet);
		std::cout << status << std::endl;
	}
}

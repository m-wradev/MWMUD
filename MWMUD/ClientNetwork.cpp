#include "ClientNetwork.h"

#include "GameScreen.h"
#include "Dispatcher.h"
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
		Dispatcher::enqueueEvent(new NetworkEvent(EVENT_TYPE::GEVT_NETWORK_CLIENT_CONNECTIONFAIL, "Failed to connect. Is the server running?"));
		return false;
	}
	else
	{
		socket.setBlocking(false);
		Dispatcher::enqueueEvent(new NetworkEvent(EVENT_TYPE::GEVT_NETWORK_CLIENT_CONNECTIONSUCCESS, ""));
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
		Dispatcher::enqueueEvent(new ChatEvent(EVENT_TYPE::GEVT_CHAT_MESSAGEDISPLAY, widestr));
	}
}

void ClientNetwork::onNotify(GameEvent* gevt)
{
	if (gevt->eventType == EVENT_TYPE::GEVT_NETWORK_CLIENT_DATASEND)
	{
		sf::Packet packet;
		packet << static_cast<NetworkEvent*>(gevt)->message;
		socket.send(packet);
	}
}

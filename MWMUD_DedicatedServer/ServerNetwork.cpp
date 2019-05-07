#include <iostream>

#include "ServerNetwork.h"
#include "Dispatcher.h"
#include "CommandParser.h"

bool ServerNetwork::init()
{
	std::cout << "Starting server..." << std::endl;

	// Bind listener to a port
	std::cout << "Binding server to port 25565..." << std::endl;
	if (listener.listen(25565) != sf::Socket::Done)
	{
		//throw std::exception("Failed to bind server to port. Is a server already running?");
		std::cout << "Failed to bind server to port. Is a server already running?" << std::endl;
		return false;
	}
	listener.setBlocking(false);	// non-blocking

	std::cout << "Registering commands..." << std::endl;
	CommandParser::init();

	std::cout << "Server started successfully.\n====================================\n";
	running = true;	// set server as running

	Dispatcher::subscribe(EVENT_TYPE::SERVER_SHUTDOWN, this);
	Dispatcher::subscribe(EVENT_TYPE::SERVER_NETWORK_CLIENTDISCONNECT, this);
	Dispatcher::subscribe(EVENT_TYPE::SERVER_MESSAGE_BROADCAST, this);
	Dispatcher::subscribe(EVENT_TYPE::SERVER_MESSAGE_DIRECT, this);

	return true;
}

void ServerNetwork::cleanup()
{
	// Broadcast that the server is shutting down
	broadcastMessage("Server is shutting down.");

	// Delete all allocated clients
	for (Client* client : clients)
		delete client;
	clients.clear();

	CommandParser::cleanup();

	// Unsubscribe from all event types
	Dispatcher::unsubscribe(EVENT_TYPE::SERVER_SHUTDOWN, this);
	Dispatcher::unsubscribe(EVENT_TYPE::SERVER_NETWORK_CLIENTDISCONNECT, this);
	Dispatcher::unsubscribe(EVENT_TYPE::SERVER_MESSAGE_BROADCAST, this);
	Dispatcher::unsubscribe(EVENT_TYPE::SERVER_MESSAGE_DIRECT, this);
}

void ServerNetwork::setRunning(bool running) { this->running = running; }
bool ServerNetwork::isRunning() { return running; }

void ServerNetwork::pollEvents()
{
	// Check for incoming clients
	// TODO -  Check if this causes a memory leak
	sf::TcpSocket* incomingSocket = new sf::TcpSocket;
	incomingSocket->setBlocking(true);
	if (listener.accept(*incomingSocket) == sf::Socket::Done)
	{
		std::cout << incomingSocket->getRemoteAddress().toString() << " connected." << std::endl;
		incomingSocket->setBlocking(false);
		clients.insert(new Client(incomingSocket));
	}
	else
	{
		delete incomingSocket;
	}

	// Check if a client sent data.
	// If they did, parse what they sent.
	for (Client* client : clients)
		if (client->sentData())
			CommandParser::parse(client->getData(), client);
}

void ServerNetwork::onNotify(Event* evt)
{
	switch (evt->eventType)
	{
	case EVENT_TYPE::SERVER_SHUTDOWN:
		cleanup();
		break;

	case EVENT_TYPE::SERVER_NETWORK_CLIENTDISCONNECT:
		disconnectClient(static_cast<ServerEvent::Network::ClientDisconnect*>(evt)->client);
		break;

	case EVENT_TYPE::SERVER_MESSAGE_BROADCAST:
		broadcastMessage(static_cast<ServerEvent::Message::Broadcast*>(evt)->msg);
		break;

	case EVENT_TYPE::SERVER_MESSAGE_DIRECT:
		ServerEvent::Message::Direct_S2C* dmEvt = static_cast<ServerEvent::Message::Direct_S2C*>(evt);
		dmEvt->recipient->sendMessage("SERVER: " + dmEvt->msg);

		break;
	}
}


/* PRIVATE MEMBER FUNCTIONS
 */
void ServerNetwork::broadcastPacket(sf::Packet packet)
{
	for (Client* client : clients)
		client->sendPacket(packet);
}

void ServerNetwork::broadcastMessage(std::string message)
{
	std::cout << message << std::endl;

	sf::Packet packet;
	packet << message;
	broadcastPacket(packet);
}

void ServerNetwork::disconnectClient(Client* client)
{
	// Always log the client out of their character first.
	client->logOut();
	std::cout << client->getIp().toString() << " disconnected." << std::endl;
	clients.erase(client);
	delete client;
}

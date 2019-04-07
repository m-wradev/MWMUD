#include <locale>
#include <codecvt>
#include <iostream>
#include <cstdio>

#include "ServerNetwork.h"

ServerNetwork::ServerNetwork()
{
	std::cout << "Starting server..." << std::endl;

	// Bind listener to a port
	if (listener.listen(25565) != sf::Socket::Done)
	{
		std::cout << "Failed to bind server to port. Is a server already running?" << std::endl;
		exit(EXIT_FAILURE);
	}
	
	listener.setBlocking(false);	// non-blocking

	std::cout << "Server started successfully.\n====================================\n";
}

ServerNetwork::~ServerNetwork()
{
	// Delete all allocated clients
	for (sf::TcpSocket* client : clients)
		delete client;
}

void ServerNetwork::pollEvents()
{
	// Start by checking to see that all clients are still connected
	std::stack<sf::TcpSocket*> toRemove;
	for (sf::TcpSocket* client : clients)
	{
		if (client->getRemoteAddress() == sf::IpAddress::None)
			toRemove.push(client);
	}

	// Remove clients that disconnected
	while (!toRemove.empty())
	{
		clients.erase(toRemove.top());
		delete toRemove.top();
		toRemove.pop();
	}

	// Check for incoming clients
	// TODO -  Check if this causes a memory leak
	sf::TcpSocket* incoming = new sf::TcpSocket;
	incoming->setBlocking(true);
	if (listener.accept(*incoming) == sf::Socket::Done)
	{
		sf::IpAddress incomingIP = incoming->getRemoteAddress();
		std::cout << incomingIP.toString() << " has connected." << std::endl;

		// Add client to set of clients
		clients.insert(incoming);

		sf::Packet packet;
		std::string toSend = incoming->getRemoteAddress().toString() + " connected.";
		packet << toSend;
		
		incoming->send(packet);
	}
	else
	{
		delete incoming;
	}

	sf::Packet incomingPacket;
	for (sf::TcpSocket* client : clients)
	{
		if (client->receive(incomingPacket) == sf::Socket::Status::Done)
		{
			std::string msg;
			incomingPacket >> msg;
			std::cout << client->getRemoteAddress().toString() << ": " << msg << std::endl;

			// Broadcast the message to all clients
			sf::Packet toBroadcast;
			toBroadcast << client->getRemoteAddress().toString() + ": " + msg;
			broadcastPacket(toBroadcast);
		}
	}
}

void ServerNetwork::cleanup()
{

}

/* PRIVATE MEMBER FUNCTIONS
 */
void ServerNetwork::broadcastPacket(sf::Packet packet)
{
	for (sf::TcpSocket* client : clients)
		client->send(packet);
}

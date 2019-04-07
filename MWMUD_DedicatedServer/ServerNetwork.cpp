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

}

void ServerNetwork::pollEvents()
{
	// Start by checking to see that all clients are still connected
	std::stack<sf::TcpSocket*> toRemove;
	for (sf::TcpSocket* client : clients)
	{
		if (client->getRemoteAddress() == sf::IpAddress::None)
		{
			// TODO - find a way to get the IP to display rather than 0.0.0.0
			// this happens because the client has already disconnected.
			std::cout << client->getRemoteAddress().toString() << " disconnected." << std::endl;
			toRemove.push(client);
		}
	}

	// Remove clients that disconnected
	while (!toRemove.empty())
	{
		clients.erase(toRemove.top());
		toRemove.pop();
	}

	// Check for incoming clients
	sf::TcpSocket incoming;
	incoming.setBlocking(false);
	if (listener.accept(incoming) == sf::Socket::Done)
	{
		sf::IpAddress incomingIP = incoming.getRemoteAddress();
		std::cout << incomingIP.toString() << " has connected." << std::endl;

		// Add client to set of clients
		//clients[incomingIP.toString()] = &incoming;
		clients.insert(&incoming);

		sf::Packet packet;
		std::string toSend = "You connected!";
		packet << toSend;
		
		//if (incoming.send("You connected!", 100) != sf::Socket::Done)
		//	std::cout << "Failed to send data to " << incomingIP.toString() << std::endl;
		incoming.send(packet);
	}
}

void ServerNetwork::cleanup()
{

}

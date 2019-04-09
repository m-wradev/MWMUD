#include <iostream>
#include <functional>
#include <sstream>

#include "ServerNetwork.h"
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

	// Register all commands
	// This might be super leaky
	std::cout << "Registering commands..." << std::endl;
	CommandParser::registerCommand("ping", new std::function<void(std::string, sf::TcpSocket*)>([this](std::string input, sf::TcpSocket* sender)
	{
		std::cout << "SERVER [to " + sender->getRemoteAddress().toString() + "]: Pong" << std::endl;

		sf::Packet p;
		p << "SERVER: Pong";
		sender->send(p);
	}));

	// Disconnect the client.
	CommandParser::registerCommand("disconnect", new std::function<void(std::string, sf::TcpSocket*)>([this](std::string input, sf::TcpSocket* sender)
	{
		std::cout << sender->getRemoteAddress().toString() << " has disconnected." << std::endl;
		sender->disconnect();
	}));

	std::cout << "Server started successfully.\n====================================\n";
	running = true;	// set server as running
	return true;
}

void ServerNetwork::setRunning(bool running) { this->running = running; }
bool ServerNetwork::isRunning() { return running; }

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

			// If the client didn't send a command, they're just sending a general message.
			// Broadcast the message to all clients.
			if (!CommandParser::parse(msg, client))
			{
				sf::Packet toBroadcast;
				toBroadcast << client->getRemoteAddress().toString() + ": " + msg;
				broadcastPacket(toBroadcast);
			}
		}
	}
}

void ServerNetwork::cleanup()
{
	// Broadcast that the server is shutting down
	broadcastMessage("Server is shutting down. Type /disconnect to return to the main menu.");

	// Delete all allocated clients
	for (sf::TcpSocket* client : clients)
		delete client;
}

/* PRIVATE MEMBER FUNCTIONS
 */
void ServerNetwork::broadcastPacket(sf::Packet packet)
{
	for (sf::TcpSocket* client : clients)
		client->send(packet);
}

void ServerNetwork::broadcastMessage(std::string message)
{
	sf::Packet packet;
	packet << "SERVER: " + message;
	broadcastPacket(packet);
}

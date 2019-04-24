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

	std::cout << "Subscribing to events..." << std::endl;
	Dispatcher::subscribe(EVENT_TYPE::SERVER_BROADCASTMESSAGE, this);
	Dispatcher::subscribe(EVENT_TYPE::SERVER_CLIENTDISCONNECT, this);
	Dispatcher::subscribe(EVENT_TYPE::SERVER_SHUTDOWN, this);

	std::cout << "Server started successfully.\n====================================\n";
	running = true;	// set server as running
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

	// Unsubscribe from all event types
	Dispatcher::unsubscribe(EVENT_TYPE::SERVER_SHUTDOWN, this);
	Dispatcher::unsubscribe(EVENT_TYPE::SERVER_CLIENTDISCONNECT, this);
	Dispatcher::unsubscribe(EVENT_TYPE::SERVER_BROADCASTMESSAGE, this);
}

void ServerNetwork::setRunning(bool running) { this->running = running; }
bool ServerNetwork::isRunning() { return running; }

void ServerNetwork::pollEvents()
{
	// Start by checking to see that all clients are still connected
	/*
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
	*/

	// Check for incoming clients
	// TODO -  Check if this causes a memory leak
	sf::TcpSocket* incomingSocket = new sf::TcpSocket;
	incomingSocket->setBlocking(true);
	if (listener.accept(*incomingSocket) == sf::Socket::Done)
	{
		/*
		sf::IpAddress incomingIP = incoming->getRemoteAddress();
		std::cout << incomingIP.toString() << " has connected." << std::endl;

		// Add client to set of clients
		clients.insert(incoming);

		sf::Packet packet;
		std::string toSend = incoming->getRemoteAddress().toString() + " connected.";
		packet << toSend;
		
		incoming->send(packet);
		*/
		incomingSocket->setBlocking(false);
		clients.insert(new Client(incomingSocket));
	}
	else
	{
		delete incomingSocket;
	}

	//sf::Packet incomingPacket;
	//for (sf::TcpSocket* client : clients)
	for (Client* client : clients)
	{
		if (client->sentData())
		{
			sf::Packet clientPacket = client->getDataPacket();
			std::string contents;
			clientPacket >> contents;
			CommandParser::parse(contents, client);
		}
		/*
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
		*/
	}
}

void ServerNetwork::onNotify(Event* evt)
{
	EVENT_TYPE& evtType = evt->eventType;
	if (evtType == EVENT_TYPE::SERVER_BROADCASTMESSAGE)
	{
		broadcastMessage(static_cast<ServerEvent::BroadcastMessage*>(evt)->msg);
	}
	else if (evtType == EVENT_TYPE::SERVER_CLIENTDISCONNECT)
	{
		disconnectClient(static_cast<ServerEvent::ClientDisconnect*>(evt)->client);
	}
	else if (evtType == EVENT_TYPE::SERVER_SHUTDOWN)
	{
		cleanup();
	}
}


/* PRIVATE MEMBER FUNCTIONS
 */
void ServerNetwork::broadcastPacket(sf::Packet packet)
{
	//for (sf::TcpSocket* client : clients)
	//	client->send(packet);
}

void ServerNetwork::broadcastMessage(std::string message)
{
	sf::Packet packet;
	packet << "SERVER: " + message;
	broadcastPacket(packet);
}

void ServerNetwork::disconnectClient(Client* client)
{
	clients.erase(client);
	delete client;
}

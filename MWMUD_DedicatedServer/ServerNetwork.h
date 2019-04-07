// TODO - set up sending/receiving with client using sfml
// TODO - find a way to detect when a client has disconnected
#pragma once

#define SFML_STATIC

#include <SFML/Network.hpp>
#include <SFML/System/Time.hpp>
#pragma comment (lib, "sfml-network-s-d.lib")
#pragma comment (lib, "sfml-system-s-d.lib")

#include <unordered_set>
#include <stack>

class ServerNetwork
{
private:
	sf::TcpListener listener;	// listens for incoming connections
	std::unordered_set<sf::TcpSocket*> clients;	// clients connected to server

	void broadcastPacket(sf::Packet);

public:
	static const int MAX_CONNECTIONS = 8;

	ServerNetwork();
	~ServerNetwork();

	void pollEvents();
	
	// clean up, shut down
	void cleanup();
};

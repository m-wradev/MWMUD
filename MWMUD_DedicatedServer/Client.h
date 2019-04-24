#pragma once

#include <SFML/Network.hpp>

#ifdef MWMUD_DEBUG
#pragma comment (lib, "sfml-network-d.lib")
#pragma comment (lib, "sfml-system-d.lib")
#endif

#ifdef MWMUD_RELEASE
#pragma comment (lib, "sfml-network.lib")
#pragma comment (lib, "sfml-system.lib")
#endif

class Client
{
private:
	sf::TcpSocket* socket;
	sf::Packet dataPacket;

public:
	Client(sf::TcpSocket*);
	~Client();

	// Check if the client sent data.
	// If they did, store the packet so that the server can retrieve it.
	bool sentData();

	const sf::Packet& getDataPacket();
};
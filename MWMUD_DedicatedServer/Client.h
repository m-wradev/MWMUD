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
	std::string data;	// data sent from a client
	std::string name;	// name used to refer to the client

	bool loggedIn;	// whether the client is logged in or not

public:
	Client(sf::TcpSocket*);
	~Client();

	// Return the name of the client.
	const std::string getName();
	// Return the client's IP.
	const sf::IpAddress getIp();

	// Return whether the client is logged in or not.
	bool isLoggedIn();
	// Log the user in, assigning them a given name.
	// Returns false if the user is already logged in.
	bool logIn(std::string name);
	// Log the user out, clearing their assigned name.
	// Returns false if the user isn't logged in.
	bool logOut();

	// Check if the client sent data.
	// If they did, store the packet so that the server can retrieve it.
	bool sentData();

	// Return the data sent by the client.
	// This action consumes the data.
	const std::string getData();

	// Send a packet to the client.
	void sendPacket(sf::Packet& packet) const;
	// Send a message to the client.
	void sendMessage(std::string msg) const;
};
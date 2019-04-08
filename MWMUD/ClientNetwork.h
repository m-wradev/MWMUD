// TODO - have the network stuff run on a separate thread
#pragma once

//#define SFML_STATIC

#include <SFML/Network.hpp>
#include <SFML/System/Time.hpp>

#ifdef MWMUD_DEBUG
#pragma comment(lib, "sfml-network-d.lib")
#pragma comment(lib, "sfml-system-d.lib")
#endif

#ifdef MWMUD_RELEASE
#pragma comment(lib, "sfml-network.lib")
#pragma comment(lib, "sfml-system.lib")
#endif

#include <string>

#include "Listener.h"
#include "GameEvent.h"

class ClientNetwork : public Listener
{
private:
	/*
	ENetHost* client;
	ENetPeer* peer;	// connection to the server
	*/

	sf::TcpSocket socket;	// socket to server

public:
	ClientNetwork();
	~ClientNetwork();

	bool connectToServer(std::string ip);
	void pollEvents();

	void onNotify(GameEvent* gevt) override;
};

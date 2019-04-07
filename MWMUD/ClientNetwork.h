// TODO - have the network stuff run on a separate thread
#pragma once

#define SFML_STATIC

#include <SFML/Network.hpp>
#include <SFML/System/Time.hpp>

#pragma comment(lib, "sfml-network-s-d.lib")
#pragma comment(lib, "sfml-system-s-d.lib")

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

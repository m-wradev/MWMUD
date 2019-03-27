#pragma once

#include <enet/enet.h>
#pragma comment(lib, "enet64.lib")

#include <string>

#include "Listener.h"
#include "GameEvent.h"

class ClientNetwork : public Listener
{
private:
	ENetHost* client;
	ENetPeer* peer;	// connection to the server

public:
	ClientNetwork();
	~ClientNetwork();

	void connectToServer(std::string ip);
	void pollEvents();

	void onNotify(GameEvent* gevt) override;
};

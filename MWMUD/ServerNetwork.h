#pragma once

#include <enet/enet.h>
#pragma comment (lib, "enet64.lib")

#include <unordered_set>

#include "Listener.h"
#include "GameEvent.h"

class ServerNetwork : public Listener
{
private:
	ENetHost* server;
	std::unordered_set<ENetPeer*> clients;

public:
	static const int MAX_CONNECTIONS = 8;

	ServerNetwork();
	~ServerNetwork();

	void pollEvents();

	void onNotify(GameEvent* gevt) override;
};
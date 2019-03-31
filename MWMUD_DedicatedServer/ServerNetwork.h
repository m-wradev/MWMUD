#pragma once

#include <enet/enet.h>
#pragma comment (lib, "enet64.lib")

#include <unordered_set>

class ServerNetwork
{
private:
	ENetHost* server;
	std::unordered_set<ENetPeer*> clients;

public:
	static const int MAX_CONNECTIONS = 8;

	ServerNetwork();
	~ServerNetwork();

	void pollEvents();
	
	// clean up, shut down
	void cleanup();
};

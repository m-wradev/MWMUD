#include <locale>
#include <codecvt>
#include <iostream>
#include <cstdio>

#include "ServerNetwork.h"

ServerNetwork::ServerNetwork()
{
	if (enet_initialize() != 0)
	{
		std::cout << "ENet failed to initialize!" << std::endl;
		exit(EXIT_FAILURE);
	}
	std::cout << "Initialized ENet successfully." << std::endl;
	std::cout << "Starting server..." << std::endl;

	ENetAddress address;

	// Bind the server to the default local host
	// Can specify host address using enet_address_set_host(&address, "x.x.x.x")
		// ACTUALLY this makes it so that the server will only accept connections from a specific address.
	address.host = ENET_HOST_ANY;
	address.port = 25565;	// bind server to port 25565

	// create the server
	server = enet_host_create
	(
		&address,	// address to bind server host to
		MAX_CONNECTIONS, // allow up to MAX_CONNECTIONS clients
		2,	// allow 2 channels to be used: 0 and 1
		0,	// assume any amount of incoming bandwidth
		0	// assume any amount of outgoing bandwidth
	);

	if (server == nullptr)
	{
		// display message stating that user could not create
		// a server.
		std::cout << "Failed to create server." << std::endl;
		
		// for now we'll just exit, but will want to change this in
		// the future.
		std::string cont;
		std::cout << "Press ENTER to exit.\n";
		std::getline(std::cin, cont);
		exit(EXIT_FAILURE);
	}

	std::cout << "Server started successfully.\n====================================\n";
}

ServerNetwork::~ServerNetwork()
{
	cleanup();
}

void ServerNetwork::pollEvents()
{
	ENetEvent enetevt;
	
	while (enet_host_service(server, &enetevt, 0) > 0)
	{
		switch (enetevt.type)
		{
			case ENET_EVENT_TYPE_CONNECT:
			{
				// just list that a client connected on the screen 
				std::cout << "Client " + std::to_string(enetevt.peer->address.host) + " connected." << std::endl;

				// Add client to list
				clients.insert(enetevt.peer);

				// notify clients of new peer connecting
				std::string toSend = "SERVER: " + std::to_string(enetevt.peer->address.host) + " connected.";
				ENetPacket* packet = enet_packet_create(toSend.c_str(), strlen(toSend.c_str()), ENET_PACKET_FLAG_RELIABLE);
				for (ENetPeer* client : clients)
					enet_peer_send(client, 0, packet);
				enet_host_flush(server);
				enet_packet_destroy(packet);

				//enetevt.peer->data = "Test Peer";
				break;
			}

			case ENET_EVENT_TYPE_RECEIVE:
			{
				// Output client's message to server console
				std::string clientID = std::to_string(enetevt.peer->address.host);
				std::string msg = std::string((char*)enetevt.packet->data);
				std::cout << clientID + ": "  + msg << std::endl;
				enet_packet_destroy(enetevt.packet);

				// Create a new packet to send to clients
				ENetPacket* packet = enet_packet_create((clientID + ": " + msg).c_str(),
					strlen((clientID + ": " + msg).c_str()), ENET_PACKET_FLAG_RELIABLE);
				
				// Deliver the message to each client
				for (ENetPeer* client : clients)
					enet_peer_send(client, 0, packet);
				enet_host_flush(server);

				// clean up the packet
				enet_packet_destroy(packet);
				break;
			}

			case ENET_EVENT_TYPE_DISCONNECT:
			{
				std::cout << "Client " + std::to_string(enetevt.peer->address.host) +  " disconnected." << std::endl;

				// Reset peer data
				//enetevt.peer->data = NULL;
				clients.erase(enetevt.peer);

				// Notify other clients of disconnect
				std::string toSend = "SERVER: " + std::to_string(enetevt.peer->address.host) + " disconnected.";
				ENetPacket* packet = enet_packet_create(toSend.c_str(), strlen(toSend.c_str()), ENET_PACKET_FLAG_RELIABLE);
				for (ENetPeer* client : clients)
					enet_peer_send(client, 0, packet);
				enet_host_flush(server);
				enet_packet_destroy(enetevt.packet);

				break;
			}
		}
	}
}

void ServerNetwork::cleanup()
{
	// notify clients of server shutdown
	ENetPacket packet;
	std::string toSend = "SERVER: SERVER SHUT DOWN.";
	enet_packet_create(toSend.c_str(), strlen(toSend.c_str()), ENET_PACKET_FLAG_RELIABLE);
	for (ENetPeer* client : clients)
		enet_peer_send(client, 0, &packet);
	enet_packet_destroy(&packet);
	enet_host_flush(server);

	enet_host_destroy(server);
}

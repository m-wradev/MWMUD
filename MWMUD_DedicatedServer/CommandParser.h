#pragma once
#include <unordered_map>
#include <unordered_set>
#include <functional>

#include "ServerNetwork.h"

class SeverNetwork;

class CommandParser
{
private:
	// Friends
	friend class ServerNetwork;

	// Commands that can be sent by the client.
	static std::unordered_set<std::string> clientCommandStrings;
	static std::unordered_map<std::string, std::function<void(std::string, sf::TcpSocket*)>*> clientCommands;

public:
	// Register commands
	static void init();
	// Deregister all commands
	static void cleanup();

	// Register a command
	static void registerCommand(std::string, std::function<void(std::string, sf::TcpSocket*)>*);
	// Deregister a command
	static void deregisterCommand(std::string);

	// Attempt to parse a command
	// If the command doesn't exist, return false.
	static bool parse(std::string, sf::TcpSocket*);
};


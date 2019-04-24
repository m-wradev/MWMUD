#pragma once

#include <vector>

#include "Client.h"

class ServerCommand
{
protected:
	std::vector<std::string> aliases;

public:
	static const char CMD_DELIM = '/';

	virtual ~ServerCommand() {}

	const std::vector<std::string> getAliases();

	// Return whether the given string matches any of the command names.
	bool match(std::string input);
	virtual void execute(std::vector<std::string> args, Client* sender) = 0;
};

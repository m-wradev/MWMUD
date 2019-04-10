#pragma once

#include <vector>

class ServerCommand
{
private:
	std::vector<std::string> aliases;

public:
	virtual ~ServerCommand() {}

	const std::vector<std::string> getAliases();

	// Return whether the given string matches any of the command names.
	bool match(std::string input);
	virtual void execute(std::vector<std::string> args) = 0;
};

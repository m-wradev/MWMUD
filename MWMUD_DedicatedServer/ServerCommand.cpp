#include "ServerCommand.h"

const std::vector<std::string> ServerCommand::getAliases() { return aliases; }

bool ServerCommand::match(std::string input)
{
	for (std::string alias : aliases)
		if (input == alias)
			return true;

	return false;
}
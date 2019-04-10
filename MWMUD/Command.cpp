#include "Command.h"

const std::vector<std::string> Command::getAliases() { return aliases; }
const std::string Command::getDescription() { return description; }
const std::string Command::getUsage() { return usage; }

bool Command::match(std::string input)
{
	// Construct regex containing aliases of the command.
	for (std::string alias : aliases)
		if (input == alias)
			return true;

	return false;
}
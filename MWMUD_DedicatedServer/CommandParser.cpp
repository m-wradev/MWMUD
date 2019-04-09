#include <thread>

#include "CommandParser.h"

//std::unordered_map<std::string, void(*)(std::string)> CommandParser::clientCommands;
std::unordered_set<std::string> CommandParser::clientCommandStrings;
std::unordered_map<std::string, std::function<void(std::string, sf::TcpSocket*)>*> CommandParser::clientCommands;

void CommandParser::init()
{
	/*====================================================================
	 *	UTILITY COMMANDS
	 *	Commands that don't involve updating or retrieving game logic
	 *====================================================================
	 */
}

void CommandParser::cleanup()
{
	for (std::string cmd : clientCommandStrings)
	{
		delete clientCommands[cmd];
		clientCommands.erase(cmd);
	}
}

void CommandParser::registerCommand(std::string cmd, std::function<void(std::string, sf::TcpSocket*)>* f)
{
	clientCommandStrings.insert(cmd);
	clientCommands[cmd] = f;
}

void CommandParser::deregisterCommand(std::string cmd)
{
	delete clientCommands[cmd];
	clientCommands.erase(cmd);
	clientCommandStrings.erase(cmd);
}

bool CommandParser::parse(std::string input, sf::TcpSocket* sender)
{
	// Input is not a command
	if (input[0] != '/')
		return false;

	auto commandEntry = clientCommands.find(input.substr(1, input.find_first_of(' ') - 1));
	if (commandEntry != clientCommands.end())
		(*(commandEntry->second))(input, sender);

	return true;
}
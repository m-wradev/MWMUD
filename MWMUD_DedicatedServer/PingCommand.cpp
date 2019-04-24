#include "PingCommand.h"

PingCommand::PingCommand()
{
	aliases.emplace_back("ping");
}

void PingCommand::execute(std::vector<std::string> args, Client* client)
{

}
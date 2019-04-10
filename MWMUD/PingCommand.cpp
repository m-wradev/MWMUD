#include "PingCommand.h"

#include "Dispatcher.h"

PingCommand::PingCommand()
{
	aliases.emplace_back("ping");
	
	description = "Ping pong!";
	usage = Command::CMD_DELIM + aliases[0];
}

void PingCommand::execute(std::vector<std::string> args)
{
	std::string msg = "";
	for (std::string s : args)
		msg += s + " ";
	msg.pop_back();

	Dispatcher::enqueueEvent(new NetworkEvent(EVENT_TYPE::GEVT_NETWORK_CLIENT_DATASEND, msg));
}
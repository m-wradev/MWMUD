#include "DisconnectCommand.h"

#include "Dispatcher.h"

DisconnectCommand::DisconnectCommand()
{
	aliases.emplace_back("disconnect");
}

void DisconnectCommand::execute(std::vector<std::string> args, Client* sender)
{
	Dispatcher::enqueueEvent(new ServerEvent::Network::ClientDisconnect(sender));
}
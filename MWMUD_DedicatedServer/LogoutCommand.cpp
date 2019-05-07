#include "LogoutCommand.h"

#include "Dispatcher.h"

LogoutCommand::LogoutCommand()
{
	aliases.emplace_back("logout");
}

void LogoutCommand::execute(std::vector<std::string> args, Client* sender)
{
	if (!sender->logOut())
		sender->sendMessage("SERVER: Must be logged in to log out.");
}
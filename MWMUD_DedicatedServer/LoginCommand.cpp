#include "LoginCommand.h"

#include "Dispatcher.h"

LoginCommand::LoginCommand()
{
	aliases.emplace_back("login");
}

void LoginCommand::execute(std::vector<std::string> args, Client* sender)
{
	sender->logIn(args[1]);
}
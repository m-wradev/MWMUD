#include "LoginCommand.h"

#include "Dispatcher.h"
#include "Util.h"

LoginCommand::LoginCommand()
{
	aliases.emplace_back("login");

	description = "Assigns the client a name within the server.";
	usage = Command::CMD_DELIM + aliases[0] + " <name>";
}

void LoginCommand::execute(std::vector<std::string> args)
{
	if (args.size() != 2)
	{
		std::wstring err = L"Malformed command.";
		Dispatcher::enqueueEvent(new ChatEvent(EVENT_TYPE::GEVT_CHAT_MESSAGEDISPLAY, err));
	}
	else
	{
		std::string msg = Util::concat_string_vec(args, ' ');

		Dispatcher::enqueueEvent(new NetworkEvent(EVENT_TYPE::GEVT_NETWORK_CLIENT_DATASEND, msg));
	}
}
#include "LogoutCommand.h"

#include "Dispatcher.h"
#include "Util.h"

LogoutCommand::LogoutCommand()
{
	aliases.emplace_back("logout");

	description = "Logs the user out of their current character.";
	usage = CMD_DELIM + aliases[0];
}

void LogoutCommand::execute(std::vector<std::string> args)
{
	if (args.size() > 1)
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
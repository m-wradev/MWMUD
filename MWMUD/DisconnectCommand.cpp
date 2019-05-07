#include "DisconnectCommand.h"

#include "TitleScreen.h"

#include "Dispatcher.h"
#include "Util.h"

DisconnectCommand::DisconnectCommand()
{
	aliases.emplace_back("disconnect");

	description = "Forcefully disconnects the client from the server and ";
	description += "returns the user back to the title screen.";
	usage = Command::CMD_DELIM + aliases[0];
}

void DisconnectCommand::execute(std::vector<std::string> args)
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
		Dispatcher::enqueueEvent(new ScreenEvent(EVENT_TYPE::GEVT_SCREEN_CLEARANDSET, new TitleScreen()));
	}
}
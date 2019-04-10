#include "DisconnectCommand.h"

#include "TitleScreen.h"

#include "Dispatcher.h"

DisconnectCommand::DisconnectCommand()
{
	aliases.emplace_back("disconnect");

	description = "Forcefully disconnects the client from the server and ";
	description += "returns the user back to the title screen.";
	usage = Command::CMD_DELIM + aliases[0];
}

void DisconnectCommand::execute(std::vector<std::string> args)
{
	std::string msg = "";
	for (std::string s : args)
		msg += s + " ";
	msg.pop_back();

	Dispatcher::enqueueEvent(new NetworkEvent(EVENT_TYPE::GEVT_NETWORK_CLIENT_DATASEND, msg));
	Dispatcher::enqueueEvent(new ScreenEvent(EVENT_TYPE::GEVT_SCREEN_CLEARANDSET, new TitleScreen()));
}
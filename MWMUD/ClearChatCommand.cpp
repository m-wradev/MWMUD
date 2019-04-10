#include "ClearChatCommand.h"

#include "Dispatcher.h"

ClearChatCommand::ClearChatCommand()
{
	aliases.emplace_back("clear");
	aliases.emplace_back("cls");

	description = "Clears all chat messages from the chat window.";
	usage = Command::CMD_DELIM + aliases[0];
}

void ClearChatCommand::execute(std::vector<std::string> args)
{
	if (args.size() > 1)
	{
		// Display too many args error
		return;
	}

	Dispatcher::enqueueEvent(new ChatEvent(EVENT_TYPE::GEVT_CHAT_CLEARCHAT, L""));
}
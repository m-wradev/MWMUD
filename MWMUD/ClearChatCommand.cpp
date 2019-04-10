#include "ClearChatCommand.h"

#include "Dispatcher.h"
#include "GameEvent.h"

ClearChatCommand::ClearChatCommand()
{
	aliases.emplace_back("clear");
	aliases.emplace_back("cls");

	description = "Clears all chat messages from the chat window.";
	usage = Command::CMD_DELIM + aliases[0];
}

bool ClearChatCommand::execute(std::vector<std::string> args)
{
	if (args.size() > 0)
	{
		// Display too many args error
	}

	Dispatcher::enqueueEvent(new ChatEvent(EVENT_TYPE::GEVT_CHAT_CLEARCHAT, L""));
}
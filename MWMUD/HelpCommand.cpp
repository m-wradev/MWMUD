#include "HelpCommand.h"

#include "CommandModules.h"

#include "Dispatcher.h"
#include "GameEvent.h"
#include "Util.h"

HelpCommand::HelpCommand()
{
	aliases.emplace_back("help");
	aliases.emplace_back("h");
	aliases.emplace_back("?");

	description = "A command that helps you use other commands.";
	usage = Command::CMD_DELIM + aliases[0] + " <command>";

	registerCommand(this);
}

HelpCommand::~HelpCommand()
{
	while (!registeredCommands.empty())
		registeredCommands.pop_back();
}

bool HelpCommand::execute(std::vector<std::string> args)
{
	std::wstring msg = L"";

	if (args.empty())
	{
		// Display all available command modules.
		msg += L"Type \"/help -m <module>\" to view available commands.\n";
		msg += L"Available command modules:\n";
		
		for (CommandModule* cmd_mod : CommandModule::getActiveModules())
			msg += L"\t" + Util::convert_string_to_wstring(cmd_mod->getName()) + L"\n";
	}
	else if (args.size() == 2 && args[0] == "-m")
	{
		// Display all commands available in a given module.
		// TODO - Get rid of this awful sentinel and rewrite this section to work without it.
		bool found = false;
		for (CommandModule* cmd_mod : CommandModule::getActiveModules())
		{
			if (Util::equalsIgnoreCase(args[1], cmd_mod->getName()))
			{
				msg += L"Commands available in module "
					+ Util::convert_string_to_wstring(cmd_mod->getName()) + L":\n";
				for (Command* cmd : cmd_mod->getCommands())
					msg += L"\t" + Util::convert_string_to_wstring(cmd->getAliases()[0]);

				found = true;
				break;
			}
		}

		if (!found)
		{
			msg += L"No command module with the name \"" + Util::convert_string_to_wstring(args[1])
				+ L"\" exists or has been registered.";
		}
	}
	else if (args.size() == 1)
	{
		// Always check to make sure the command exists.
		Command* cmd = nullptr;
		for (Command* c : registeredCommands)
			if (c->match(args[0]))
				cmd = c;

		if (cmd != nullptr)
		{
			msg += L"Command:\t" + Util::convert_string_to_wstring(cmd->getAliases()[0]) + L"\n";
			msg += L"Description:\t" + Util::convert_string_to_wstring(cmd->getDescription()) + L"\n";
			msg += L"Usage:\t\t" + Util::convert_string_to_wstring(cmd->getUsage()) + L"\n";
			msg += L"Aliases:\t\t";
			for (std::string alias : cmd->getAliases())
				msg += Util::convert_string_to_wstring(alias) + L", ";
			msg.pop_back(); msg.pop_back();
		}
		else
		{
			msg += L"No information available. A command with the alias \""
				+ Util::convert_string_to_wstring(args[0]) + L"\" either doesn't exist or isn\'t "
				+ L"registered with the help command.";
		}
	}

	Dispatcher::enqueueEvent(new ChatEvent(EVENT_TYPE::GEVT_CHAT_MESSAGEDISPLAY, msg));
}

void HelpCommand::registerCommand(Command* cmd)
{
	registeredCommands.push_back(cmd);
}

void HelpCommand::deregisterCommand(Command* cmd)
{
	registeredCommands.push_back(cmd);
}

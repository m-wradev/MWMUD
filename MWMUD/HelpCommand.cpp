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

void HelpCommand::execute(std::vector<std::string> args)
{
	std::string msg = "";

	if (args.size() == 1)
	{
		// Display all available command modules.
		msg += "Type \"/help -m <module>\" to view available commands.\n";
		msg += "Available command modules:\n";
		
		for (CommandModule* cmd_mod : CommandModule::getActiveModules())
			msg += "\t" + cmd_mod->getName() + "\n";
		msg.pop_back();
	}
	else if (args.size() == 3 && args[1] == "-m")
	{
		// Display all commands available in a given module.
		// TODO - Get rid of this awful sentinel and rewrite this section to work without it.
		bool found = false;
		for (CommandModule* cmd_mod : CommandModule::getActiveModules())
		{
			if (Util::equals_ignore_case(args[2], cmd_mod->getName()))
			{
				// TODO - Add line break after every 5 commands.
				msg += "Commands available in module " + cmd_mod->getName() + ":\n";
				for (Command* cmd : cmd_mod->getCommands())
					msg += "\t" + cmd->getAliases()[0];

				found = true;
				break;
			}
		}

		if (!found)
			msg += "No command module with the name \"" + args[2] + "\" exists or has been registered.";
	}
	else if (args.size() == 2)
	{
		// Always check to make sure the command exists.
		Command* cmd = nullptr;
		for (Command* c : registeredCommands)
			if (c->match(args[1]))
				cmd = c;

		if (cmd != nullptr)
		{
			msg += "Command:\t" + cmd->getAliases()[0] + "\n";
			msg += "Description:\t" + cmd->getDescription() + "\n";
			msg += "Usage:\t\t" + cmd->getUsage() + "\n";
			msg += "Aliases:\t\t";
			for (std::string alias : cmd->getAliases())
				msg += alias + ", ";
			msg.pop_back(); msg.pop_back();
		}
		else
		{
			msg += "No information available. A command with the alias \""
				+ args[1] + "\" either doesn't exist or isn\'t "
				+ "registered with the help command.";
		}
	}

	msg += "\n"; // Add a nice little break at the end to make reading easier on the eyes.
	Dispatcher::enqueueEvent(new ChatEvent(EVENT_TYPE::GEVT_CHAT_MESSAGEDISPLAY, Util::convert_string_to_wstring(msg)));
}

void HelpCommand::registerCommand(Command* cmd)
{
	registeredCommands.push_back(cmd);
}

void HelpCommand::deregisterCommand(Command* cmd)
{
	registeredCommands.push_back(cmd);
}

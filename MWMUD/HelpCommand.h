#pragma once
#include "Command.h"

#include <vector>

class HelpCommand : public Command
{
private:
	std::vector<Command*> registeredCommands;

public:
	HelpCommand();
	~HelpCommand();

	bool execute(std::vector<std::string> args) override;
	void registerCommand(Command* cmd);
	void deregisterCommand(Command* cmd);
};

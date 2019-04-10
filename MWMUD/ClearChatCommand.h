#pragma once

#include "Command.h"

class ClearChatCommand : public Command
{
public:
	ClearChatCommand();

	void execute(std::vector<std::string> args) override;
};

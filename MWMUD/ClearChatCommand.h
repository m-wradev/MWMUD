#pragma once

#include "Command.h"

class ClearChatCommand : public Command
{
private:

public:
	ClearChatCommand();

	bool execute(std::vector<std::string> args) override;
};

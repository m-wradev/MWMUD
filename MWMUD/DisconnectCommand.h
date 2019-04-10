#pragma once

#include "Command.h"

class DisconnectCommand : public Command
{
public:
	DisconnectCommand();

	void execute(std::vector<std::string> args) override;
};

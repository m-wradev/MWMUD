#pragma once

#include "Command.h"

class LogoutCommand : public Command
{
public:
	LogoutCommand();

	/* Command:	Logout
	 * Module:	Network
	 * 
	 * Aliases:	logout
	 * Usage:	/logout
	 * Args:	n/a
	 *
	 * Logs the user out of their current character.
	 */
	void execute(std::vector<std::string> args) override;
};
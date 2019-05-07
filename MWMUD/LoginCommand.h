#pragma once

#include "Command.h"

class LoginCommand : public Command
{
public:
	LoginCommand();

	/* Command:	Login
	 * Module:	Network
	 * 
	 * Aliases: login
	 * Args:	<name> - name to log in as
	 * Usage:	/login <name>
	 *
	 * Logs the user in with a name.
	 */
	void execute(std::vector<std::string> args) override;
};
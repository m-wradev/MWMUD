#pragma once

#include "ServerCommand.h"

class LogoutCommand : public ServerCommand
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
	 * Logs the client out of their character.
	 */
	void execute(std::vector<std::string> args, Client* sender) override;
};

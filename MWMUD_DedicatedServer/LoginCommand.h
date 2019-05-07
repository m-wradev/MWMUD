#pragma once

#include "ServerCommand.h"

class LoginCommand : public ServerCommand
{
public:
	LoginCommand();

	/* Command:	Login
	 * Module:	Network
	 *
	 * Aliases:	login
	 * Usage:	/login <name>
	 * Args:	<name> - name to log the client in as
	 *
	 * Assigns a client a name that'll be displayed when messages are sent and recieved.
	 */
	void execute(std::vector<std::string> args, Client* sender) override;
};

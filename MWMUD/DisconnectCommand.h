#pragma once

#include "Command.h"

class DisconnectCommand : public Command
{
public:
	DisconnectCommand();

	/* Command:	Disconnect
	 * Module:	Network
	 *
	 * Aliases:	disconnect
	 * Args:	n/a
	 * Usage:	/disconnect
	 *
	 * Send a request to the server to disconnect.
	 * Returns the user to the main menu.
	 */
	void execute(std::vector<std::string> args) override;
};

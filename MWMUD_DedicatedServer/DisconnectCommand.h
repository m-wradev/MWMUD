#pragma once

#include "ServerCommand.h"

class DisconnectCommand : public ServerCommand
{
public:
	DisconnectCommand();

	/* Command:	Disconnect
	 * Module:	Network
	 *
	 * Aliases: disconnect
	 * Args:	n/a
	 *
	 * Removes the given client from the list of connected users.
	 * Broadcasts a message that a user disconnected.
	 */
	void execute(std::vector<std::string> args, Client* sender) override;
};
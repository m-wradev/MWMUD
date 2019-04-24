#pragma once

#include "ServerCommand.h"

class PingCommand : public ServerCommand
{
public:
	PingCommand();

	/* Command:	Ping
	 * Module:	Network
	 *
	 * Aliases: Ping
	 * Args:	n/a
	 *
	 * Used to measure latency.  When a client pings the server, the server will
	 * send a simple response.
	 */
	void execute(std::vector<std::string> args, Client* client) override;
};

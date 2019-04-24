#pragma once

#include "Command.h"

class PingCommand : public Command
{
public:
	PingCommand();

	/* Command:	Ping
	 * Module:	Network
	 *
	 * Aliases:	Ping
	 * Args:	n/a
	 * Usage:	/ping
	 *
	 * Used to measure latency.  Pings the server and displays the latency when the
	 * server responds with a pong.
	 */
	void execute(std::vector<std::string> args) override;
};

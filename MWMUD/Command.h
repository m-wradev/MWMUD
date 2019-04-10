#pragma once

#include <vector>

class Command
{
private:

protected:
	std::vector<std::string> aliases;
	std::string description;
	std::string usage;

public:
	static const char CMD_DELIM = '/';

	virtual ~Command() {}

	const std::vector<std::string> getAliases();
	const std::string getDescription();
	const std::string getUsage();

	// Return whether the given string matches any of the command's aliases.
	bool match(std::string);

	// The first element of the args vector will always be the command being executed.
	virtual void execute(std::vector<std::string> args) = 0;
};
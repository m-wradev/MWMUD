#pragma once

#include <vector>

class Command
{
private:

protected:
	std::vector<std::string> aliases;
	std::string description;
	std::string usage;
	std::string module;

public:
	static const char CMD_DELIM = '/';

	const std::vector<std::string> getAliases();
	const std::string getDescription();
	const std::string getUsage();

	// Return whether the given string matches any of the command's aliases.
	bool match(std::string);

	virtual bool execute(std::vector<std::string> params) = 0;
};
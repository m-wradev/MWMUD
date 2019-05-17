#pragma once

#include <vector>
#include <string>
#include <unordered_map>

class Area
{
private:
	static std::unordered_map<std::string, Area*> areas;

	Area();
	~Area();

	std::string id;
	std::string name;
	std::string description;

public:

};

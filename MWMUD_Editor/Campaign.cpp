#include "Campaign.h"

#include <iostream>
#include <filesystem>
#include <fstream>
#include <sstream> 
#include <cstring>

/* STATIC MEMBERS
 */
static bool loaded = false;				// Is a campaign currently loaded?

// Campaign Properties
static std::string directory;
static std::string name;
static std::string author;
static std::string description;

/*
 * FUNCTIONS
 */

/* General */
void Campaign::create()
{
	// Print campaign properties information
	std::cout << "Creating campaign: " << std::endl;
	std::cout << "\tDirectory: " << directory << std::endl;
	std::cout << "\tName: " << name << std::endl;
	std::cout << "\tAuthor: " << author << std::endl;
	std::cout << "\tDescription: " << description << std::endl;

	// Create directory for campaign and write properties to file
	std::filesystem::create_directory(CAMPAIGNS_DIR + '\\' + directory);
	std::ofstream propertiesFile(CAMPAIGNS_DIR + "\\" + directory + "\\campaign.properties");
	propertiesFile << "name = " << name << "\n";
	propertiesFile << "author = " << author << "\n";
	propertiesFile << "description = " << description << "\n";
	propertiesFile.close();

	// Create directory for game data
	std::string gameDataDir = CAMPAIGNS_DIR + '\\' + directory + "\\game_data";
	std::filesystem::create_directory(gameDataDir);

	// Create directory for editor data
	std::string editorDataDir = CAMPAIGNS_DIR + '\\' + directory + "\\editor_data";
	std::filesystem::create_directory(editorDataDir);

	// Create file for storing area data
	std::ofstream areasFile(gameDataDir + "\\areas.dat");
	areasFile.close();
	
	/*
	// Create file for storing editor groupings for areas
	std::ofstream areaGroupsFile(editorDataDir + "\\areas.groups");
	areaGroupsFile.close();
	*/
}

void Campaign::open(std::string campaignDir)
{
	directory = campaignDir;

	std::string line;

	// Load properties
	std::ifstream propertiesFile(CAMPAIGNS_DIR + "\\" + directory + "\\campaign.properties");
	std::getline(propertiesFile, line); name = line.substr(line.find_first_of('=') + 2);
	std::getline(propertiesFile, line); author = line.substr(line.find_first_of('=') + 2);
	std::getline(propertiesFile, line); description = line.substr(line.find_first_of('=') + 2);
	propertiesFile.close();

	std::cout << "Loaded campaign:" << std::endl;
	std::cout << "\tDirectory: " << directory << std::endl;
	std::cout << "\tName: " << name << std::endl;
	std::cout << "\tAuthor: " << author << std::endl;
	std::cout << "\tDescription: " << description << std::endl;

	loaded = true;
}

void Campaign::close()
{
	if (!loaded) return;

	std::cout << "Closed campaign." << std::endl;

	loaded = false;
}

void Campaign::save()
{
	if (!loaded) return;
}


/* Campaign Properties */
void Campaign::setProperties(char* _dir, char* _name, char* _author, char* _desc)
{
	directory	= _dir;
	name		= _name;
	author		= _author;
	description	= _desc;
}

/* Getters */
std::string Campaign::getName() { return name; }
std::string Campaign::getAuthor() { return author; }

std::string Campaign::getLoadedCampaignDirectory() 
{ 
	if (loaded)
		return CAMPAIGNS_DIR + '\\' + directory;
	else
		return "";
}

bool Campaign::isLoaded()
{
	return loaded;
}

bool Campaign::hasUnsavedChanges()
{
	if (!loaded) return false;

	return false;
}

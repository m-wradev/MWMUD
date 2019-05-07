#pragma once

#include <string>

namespace Campaign
{
	/*
	 * VISIBLE CONSTANTS
	 */
	const std::string CAMPAIGNS_DIR = ".\\Campaigns";
	const std::string PROPERTIES_FILENAME = "campaign.properties";

	/*
	 * FUNCTIONS
	 */
	/* General */
	// Create and open a new campaign for editing.
	void create();
	// Open a campaign for editing.
	void open(std::string campaign);
	// Close the current campaign.  Will only work if a campaign is loaded.
	void close();
	// Save a campaign.
	void save();

	/* Campaign Properties */
	// Set campaign properties
	void setProperties(char* _dir, char* _name, char* _author, char* _desc);
	std::string getName();
	std::string getAuthor();

	/* Campaign Status */
	// Return whether a campaign is loaded or not.
	bool isLoaded();
	// Return whether a campaign has unsaved changes or not.
	bool hasUnsavedChanges();
};
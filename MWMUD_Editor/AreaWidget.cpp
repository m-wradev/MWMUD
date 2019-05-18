#include "AreaWidget.h"

#include "Dependencies/nlohmann/json.hpp"
#include "Campaign.h"

#include <iostream>
#include <forward_list>
#include <fstream>

const std::string AreaWidget::AREAS_GROUPS_PATH = "\\editor_data\\areas.groups";

AreaWidget::AreaWidget()
{
	/*
	// Saved tree structure
	std::ofstream savedGroups;

	// Check if the areas.groups file exists.  If not, create it.
	if (!std::ifstream(Campaign::getLoadedCampaignDirectory() + AREAS_GROUPS_PATH))
	{
		//nlohmann::json initJson = {};
	}
	// Otherwise, load up the groups.
	else
	{

	}
	*/

	// Item 0
	treeView.root->children.push_back(new ItemNode("ITEM_0"));

	// Create group A
	treeView.root->children.push_back(new GroupNode("GROUP_A"));
	static_cast<GroupNode*>(treeView.root->children.back())->children.push_back(new ItemNode("ITEM_1"));
	static_cast<GroupNode*>(treeView.root->children.back())->children.push_back(new ItemNode("ITEM_2"));

	std::cout << std::endl;
	nlohmann::json json = treeView;
	std::cout << json << std::endl;
}

void AreaWidget::draw()
{

}
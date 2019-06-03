#include "AreaWidget.h"

#include "Dependencies/nlohmann/json.hpp"
#include "Campaign.h"

#include <iostream>
#include <forward_list>
#include <fstream>

const std::string AreaWidget::AREAS_REFIDTREE_PATH = "\\editor_data\\areas.groups";

AreaWidget::AreaWidget()
{
	// If JSON data for the area tree exists, load it
	if (std::ifstream(Campaign::getLoadedCampaignDirectory() + AREAS_REFIDTREE_PATH))
		treeView.loadFromJSON(Campaign::getLoadedCampaignDirectory() + AREAS_REFIDTREE_PATH);
}

void AreaWidget::draw()
{

}
#pragma once
#include "Dependencies/imgui/imgui.h"
#include "Dependencies/imgui/imgui-SFML.h"

#include "Widget.h"
#include "Campaign.h"

#include <vector>
#include <string>

class CampaignWidget : public Widget
{
private:
	std::vector<std::string> campaignDirs;
	std::string selectedCampaign = "";

	// Campaign properties
	char camp_dir[64];
	char camp_name[64];
	char camp_author[64];
	char camp_desc[256];

	// Modal visibility
	bool show_edit_properties_modal = false;

	// Retrieve all campaigns available in the Campaigns directory
	// and place their directories into campaignDirs.
	void retrieveCampaignDirectories();

public:
	CampaignWidget();

	void draw() override;
};
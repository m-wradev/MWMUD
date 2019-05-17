#include "CampaignWidget.h"

#include <iostream>
#include <filesystem>

CampaignWidget::CampaignWidget()
{
	retrieveCampaignDirectories();
}

// TODO - move non-drawing logic out of the draw method
void CampaignWidget::draw()
{
	if (!Campaign::isLoaded())
		ImGui::Begin("Load or Create Campaign", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar);
	else
		ImGui::Begin(("Campaign: " + Campaign::getName()).c_str(), NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar);

	// Draw menu bar
	if (ImGui::BeginMenuBar())
	{
		// File Menu
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Save Campaign", NULL, false, Campaign::isLoaded()))
			{

			}

			if (ImGui::MenuItem("Close Campaign", NULL, false, Campaign::isLoaded()))
			{
				Campaign::close();
			}

			ImGui::EndMenu();
		}

		ImGui::EndMenuBar();
	}

	// If campaign isn't loaded, display campaign selection
	if (!Campaign::isLoaded())
	{
		// Show available campaigns
		ImGui::Text("Available Campaign Directories:");
		if (ImGui::ListBoxHeader("", campaignDirs.size(), 10))
		{
			// Display each campaign as a selectable option
			for (const std::string& campaignDir : campaignDirs)
				if (ImGui::Selectable(campaignDir.c_str(), selectedCampaign == campaignDir))
					selectedCampaign = campaignDir;
			ImGui::ListBoxFooter();

			// Open the selected campaign
			if (ImGui::Button("Load Campaign"))
				if (selectedCampaign != "")
					Campaign::open(selectedCampaign);
		}

		// New campaign
		ImGui::Separator();
		ImGui::Text("Create New Campaign ('*' indicates required field):");
		ImGui::InputText("*Directory", camp_dir, IM_ARRAYSIZE(camp_dir), ImGuiInputTextFlags_CharsNoBlank);
		ImGui::InputText("*Name", camp_name, IM_ARRAYSIZE(camp_name));
		ImGui::InputText("Author", camp_author, IM_ARRAYSIZE(camp_author));
		ImGui::InputTextMultiline("Description", camp_desc, IM_ARRAYSIZE(camp_desc));
		
		if (ImGui::Button("Create"))
		{
			// Campaign directory and name must be provided.
			if (strlen(camp_dir) > 0 && strlen(camp_name) > 0)
			{
				Campaign::setProperties(camp_dir, camp_name, camp_author, camp_desc);
				Campaign::create();
				retrieveCampaignDirectories();
			}
			else
			{
				ImGui::OpenPopup("ERR_REQUIRED_FIELD_EMPTY");
			}
		}

		// Contextual popup if user tries to create a campaign but required fields are empty
		if (ImGui::BeginPopupContextItem("ERR_REQUIRED_FIELD_EMPTY"))
		{
			std::string err_msg = "Required fields are empty:\n";
			if (strlen(camp_dir) == 0) err_msg += "\tDirectory\n";
			if (strlen(camp_name) == 0) err_msg += "\tName\n";
			ImGui::TextColored(ImVec4(1.0, 0.0, 0.0, 1.0), err_msg.c_str());

			ImGui::EndPopup();
		}
	}
	// Else, we can show all campaign-related settings and options
	else
	{
		ImGui::Text(("Campaign: " + Campaign::getName()).c_str());
		ImGui::Text(("Author: " + Campaign::getAuthor()).c_str());

		ImGui::Separator();

		if (ImGui::Button("Edit Properties"))
		{
			ImGui::OpenPopup("Campaign Properties");
			show_edit_properties_modal = true;
		}

		// Campaign properties modal 
		if (ImGui::BeginPopupModal("Campaign Properties", &show_edit_properties_modal, ImGuiWindowFlags_AlwaysAutoResize))
		{
			ImGui::Text("Edit campaign properties (* indicates required field):");
			ImGui::InputText("*Name", camp_name, IM_ARRAYSIZE(camp_name));
			ImGui::InputText("Author", camp_author, IM_ARRAYSIZE(camp_author));
			ImGui::InputTextMultiline("Description", camp_desc, IM_ARRAYSIZE(camp_desc));

			// Update properties
			if (ImGui::Button("Update"))
			{

			}

			ImGui::SameLine();

			// Cancel edit
			if (ImGui::Button("Cancel"))
			{
				show_edit_properties_modal = false;
			}

			ImGui::EndPopup();
		}
	}

	ImGui::End();
}

void CampaignWidget::retrieveCampaignDirectories()
{
	std::cout << "Available campaigns: " << std::endl;
	campaignDirs.clear();
	for (auto& p : std::filesystem::directory_iterator(Campaign::CAMPAIGNS_DIR))
	{
		if (p.status().type() == std::filesystem::file_type::directory)
		{
			std::string campaignPath = p.path().string();
			std::cout << p.path().string() << std::endl;
			campaignDirs.push_back(campaignPath.substr(campaignPath.find_last_of('\\') + 1));
		}
	}
}
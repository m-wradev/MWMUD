#include "Editor.h"

#include "Campaign.h"
#include "Widgets.hpp"

#include <iostream>

/* STATIC MEMBERS
 */
static Editor::STATUS editorStatus = Editor::STATUS::UNINIT;
static sf::RenderWindow editorWindow(sf::VideoMode(1366, 768), "MWMUD Editor");
static sf::Clock deltaClock;
static std::vector<Widget*> widgets;

/* VISIBLE MEMBER METHODS
 */
void Editor::init()
{
	editorWindow.setFramerateLimit(60);
	ImGui::SFML::Init(editorWindow);

	widgets.push_back(new CampaignWidget());
	widgets.push_back(new AreaWidget());

	editorStatus = STATUS::RUNNING;
}

void Editor::cleanup()
{
	ImGui::SFML::Shutdown();

	while (!widgets.empty())
	{
		delete widgets.back();
		widgets.pop_back();
	}

	if (Campaign::isLoaded())
		Campaign::close();

	editorStatus = STATUS::TERMINATED;
}

void Editor::update()
{
	// Logic updates here
	sf::Event windowEvent;
	while (editorWindow.pollEvent(windowEvent))
	{
		ImGui::SFML::ProcessEvent(windowEvent);

		if (windowEvent.type == sf::Event::Closed)
		{
			// Display warning if campaign has unsaved changes.
			/*
			if (Campaign::isLoaded() && Campaign::hasUnsavedChanges())
			{ 

			}
			*/

			std::cout << "Shutting down engine." << std::endl;

			editorWindow.close();
			cleanup();
		}
	}
}

void Editor::draw()
{
	ImGui::SFML::Update(editorWindow, deltaClock.restart());

	// Drawing here
	for (Widget* widget : widgets)
		widget->draw();
	
	editorWindow.clear();
	ImGui::SFML::Render(editorWindow);
	editorWindow.display();
}

Editor::STATUS Editor::getStatus() { return editorStatus; }

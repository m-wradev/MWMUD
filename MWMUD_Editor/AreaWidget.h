#pragma once

#include "Widget.h"

#include "RefIdTree.h"

#include <string>

class AreaWidget : public Widget
{
private:

public:
	static const std::string AREAS_GROUPS_PATH;	// Path to saved area organization in widget tree

	RefIdTree treeView;	// Grouped areas in a tree view

	AreaWidget();

	void draw() override;
};

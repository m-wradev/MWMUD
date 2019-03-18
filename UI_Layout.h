#pragma once
class UI_Layout
{
	std::stack<UI_Element> ui_elements;

public:
	UI_Layout();
	~UI_Layout();
};


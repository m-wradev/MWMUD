// TODO - Create dispatcher system for engine.  Engine shutdown should be first priority.
#include "Editor.h"

int main()
{
	Editor::init();
	while (Editor::getStatus() == Editor::STATUS::RUNNING)
	{
		/*
		Engine::update();
		Engine::draw();
		*/

		// Until dispatcher system implemented, must draw first.
		// Engine will crash if we close the window in Engine::update()
		// before Engine::draw().
		Editor::draw();
		Editor::update();
	}

	if (Editor::getStatus() == Editor::STATUS::ERROR)
	{
		// Print error info here.
	}

	return 0;
}
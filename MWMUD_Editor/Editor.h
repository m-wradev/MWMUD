#pragma once

#include "Dependencies/imgui/imgui.h"
#include "Dependencies/imgui/imgui-SFML.h"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#ifdef MWMUD_DEBUG
#pragma comment (lib, "sfml-window-d.lib")
#pragma comment (lib, "sfml-graphics-d.lib")
#pragma comment (lib, "sfml-system-d.lib")
#endif

#ifdef MWMUD_RELEASE
#pragma comment (lib, "sfml-window.lib")
#pragma comment (lib, "sfml-graphics.lib")
#pragma comment (lib, "sfml-system.lib")
#endif

#include <string>

namespace Editor
{
	enum STATUS
	{
		UNINIT,		// Engine hasn't been initialized
		RUNNING,	// Engine is running
		TERMINATED, // Engine has been shut down
		ERROR		// Engine encountered an error
	};

	/* VISIBLE CONSTANTS
	 */

	/* VISIBLE FUNCTIONS
	 */
	// Initialize the editor
	void init();
	// Clean up the editor to prepare for shutdown
	void cleanup();

	// Perform logic updates
	void update();
	// Draw the editor
	void draw();

	// Returns whether the editor is running or not
	STATUS getStatus();


	/* STATIC FUNCTIONS
	 */
};

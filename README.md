Note:  At some point I'm going to be using cmake to aid in the setup process.  At the moment the setup process is clunky.

# About
I hadn't planned on making this public but I figured it'd be nice to show to employers during my job hunt.  As such, I'm still in the process of writing up better documentation for the project overall.
It should be noted that this is more of a personal experiment and a device I've been using to learn about topics such as engine development, basic networking, event-driven programming, and game design.  I've also been using it to become familiar with APIs and SDKs
such as SFML and DirectX (Direct2D and DirectWrite, more specifically). 
Since it's my first time designing and developing what I may be naively referring to as an "engine", there are definitely going to be awkward design choices, funky workarounds for easily-preventable problems, probably way too many dynamic allocations and pointers, 
and other silly mistakes that you'd expect from someone who's never done this before.
If I ever finish or get bored developing this project, I plan to work on 2D and 3D games using DirectX, OpenGL, or Vulkan.

MWMUD is going to be a cooperative MUD-like game meant to be played with a small group of friends.  I have several gameplay features planned and roughly designed but I have yet to implement any as I'm still building the technology for the game.
There's also no guarantee that this will ever be finished or completed.

The project currently consists of three executable files, two of which are required to actually play the game:
* MWMUD - The client through which the player will interact with the server.
* MWMUD\_DedicatedServer - The server which will handle game logic.
* MWMUD\_Editor - The editor used to build campaigns for the server to run.

# Setup
MWMUD is being developed in Visual Studio 2017, so you'll need that in order to build and run the projects in the solution.

Note: There's currently a problem building the Release x64 configuration of MWMUD\_Editor.

You'll need to edit the following properties for each of the projects in order to successfully build:
* MWMUD
	* All Configurations
		* VC++ Directories -> Library Directories - Add path to DirectX SDK `Lib/x64` directory.
		* C/C++ -> General -> Additional Include Directories - Add path to SFML-2.5.1 `include` directory.
		* Linker -> General -> Additional Library Directories - Add path to SFML-2.5.1 `lib` directory.
		* Linker -> Input -> Additional Dependencies - Make sure `ws2_32.lib` and `winmm.lib` are listed.
	* Debug (x64)
		* VC++ Directories -> Executable Directories - Add path to DirectX SDK executable at `[path to DirectX SDK]/Utilities/bin/x64`.
		* Linker -> Input -> Additional Dependencies - Add `sfml-network-d.lib` and `sfml-system-d.lib` as additional dependencies.
	* Release (x64)
		* VC++ Directories -> Include Directories - Add path to DirectX SDK `Include` directory. 
		* Linker -> Input -> Additional Depencies - Add `sfml-network.lib` and `sfml-system.lib` as additional dependencies.
* MWMUD\_DedicatedServer
	* All Configurations
		* C/C++ -> General -> Additional Include Directories - Add path to SFML-2.5.1 `include` directory.
		* Linker -> General -> Additional Library Directories - Add path to SFML-2.5.1 `lib` directory.
		* Linker -> Input -> Additional Dependencies - Make sure `ws2_32.lib` and `winmm.lib` are listed.
	* Debug (x64)
		* Linker -> Input -> Additional Dependencies - Add `sfml-network-d.lib` and `sfml-system-d.lib` as additional dependencies.
	* Release (x64)
		* Linker -> Input -> Additional Depencies - Add `sfml-network.lib` and `sfml-system.lib` as additional dependencies.
* MWMUD\_Editor
	* All Configurations
		* C/C++ -> General -> Additional Include Directories - Add path to SFML-2.5.1 `include` directory.
		* Linker -> General -> Additional Library Directories - Add the paths to the following directories:
			* glew-2.1.0: `lib/Release/x64`
			* SFML-2.5.1: `lib`
	* Debug (x64)
		* Linker -> Input -> Additional Dependencies - add `sfml-graphics-d.lib`, `sfml-system-d.lib`, `sfml-window-d.lib`, `glew32.lib`, and `opengl32.lib` as additional dependencies.
	* Release (x64)
		* This configuration is currently broken and fails to build.  I'll update this section when/if I fix it.

If MWMUD or MWMUD\_DedicatedServer fail to build or run, you may need to drop the specified SFML .dll files into the intermediate `/x64/Debug` and `/x64/Release` directories.

# Testing the Client and Server
The server currently tries to bind itself to port 25565 (yes, Minecraft's default port) and uses the TCP protocol for network communication.  You may have to forward the port in order to communicate with computers outside of your local network.
In the future, I'll have the server read from a properties or configuration file, allowing the user to specify things such as port, IP address, MotD, etc.

Here are the basic steps to follow in order to get the server and client communicating on your own computer:
1. Run MWMUD\_DedicatedServer.exe.  Both Release and Debug should work.
2. Run MWMUD.exe.
3. Follow the prompts and use the arrow keys to navigate to the Join Game option.
4. Since you're running the server on the same computer as the client, you don't have to enter a server IP.  Highlight "Join" and press enter.
5. If I've typed this up correctly and everything works, you should see a black screen.  Looking at the server will show that a client has connected and your internal IP should be displayed.
6. Type /help, /h, or /? to view available modules.  You can also type /help help to view helpful information about the help command.  I'll have to update the usage information since it seems to be slightly out of date.  Note that all commands are prefixed with "/".
7. To relay a message to all clients connected to the server, simply enter a string that isn't prefixed by "/" and press enter.  You'll find that the server won't let you send messages until you're logged in.  Use the help command to view information about the login command.
8. Use the login command to log in.  Try sending some messages and using some of the available commands.  A few don't do anything at the moment since I haven't reimplemented their functionality after reworking the general command structure for both the client and server.
9. When satisfied with the knowledge that you were able to test in under a minute what I spent hours trying to implement, or when you've grown bored of playing around with software that currently doesn't do much of anything, use the logout command to log out.  You can then use the disconnect command to return to the title screen.  If you like to live dangerously, you can use the disconnect command without first logging out.  Don't worry though.  The server will log you out, preserving the sanctity of your currently non-existent character data while allowing you to maintain your precious ego.  You probably just yank your flash drive from the computer without ejecting it first too, don't you?
10. Close the server window.  It should shut down and display a message stating such before prompting you to press a key to close the window.

# Using the Editor
I'll update this section when the editor is more complete than it currently is.

# Dependencies
* DirectX - for the client UI (should have probably used something else)
* SFML - for the networking
* ImGui (https://github.com/ocornut/imgui) - Editor UI
* ImGui-SFML (https://github.com/eliasdaler/imgui-sfml) - Editor UI
* JSON for Modern C++ (https://github.com/nlohmann/json) - Saving campaign data

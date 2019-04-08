// MWMUD_DedicatedServer.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <string>
#include <exception>
#include <Windows.h>

// TODO: server input
#include "ServerNetwork.h"
#include "CommandParser.h"

// CONSOLE HANDLER ROUTINE
BOOL WINAPI consoleHandler(DWORD dwCtrlType);

void cleanup();
void displayShutdownMessage();

ServerNetwork server;

int main()
{
	std::cout << "MWMUD prealpha version" << std::endl;
	std::cout << std::endl;

	SetConsoleCtrlHandler(consoleHandler, TRUE);

	// START SERVER
	if (!server.init())
		displayShutdownMessage();

	while (server.isRunning())
	{
		try
		{
			server.pollEvents();
		}
		catch (std::exception& e)
		{
			std::cout << "Server encountered an error from which it couldn't recover." << std::endl;
			std::cout << "ERROR: " << e.what() << std::endl;
			std::cout << std::endl;
			
			server.setRunning(false);
		}

		Sleep(20);
	}

	displayShutdownMessage();
	cleanup();
	return 0;
}

BOOL WINAPI consoleHandler(DWORD dwCtrlType)
{
	if (dwCtrlType == CTRL_C_EVENT || dwCtrlType == CTRL_CLOSE_EVENT)
	{
		displayShutdownMessage();
		cleanup();
		ExitProcess(0);
	}

	return FALSE;
}

void cleanup()
{
	server.cleanup();
	CommandParser::cleanup();
}

void displayShutdownMessage()
{
	std::cout << "Server is shutting down.  Press ENTER to continue.";
	std::string throwaway;
	std::getline(std::cin, throwaway);
}
// MWMUD_DedicatedServer.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
#include <string>
#include <exception>
#include <Windows.h>

// TODO: server input
#include "ServerNetwork.h"
#include "Dispatcher.h"
#include "CommandParser.h"

// debug memory leaks
#ifdef MWMUD_DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

BOOL WINAPI consoleHandler(DWORD dwCtrlType);
void cleanup();
void displayShutdownMessage();

ServerNetwork server;

int main()
{
	// Get memory leak report at each exit point
	#ifdef MWMUD_DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	#endif

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
			Dispatcher::flushEvents();
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
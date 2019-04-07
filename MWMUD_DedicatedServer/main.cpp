// MWMUD_DedicatedServer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <exception>
#include <Windows.h>

// TODO: server input
#include "ServerNetwork.h"

int main()
{
	/*
	std::string ip;
	std::cout << "Enter the IP that will host the server: ";
	std::getline(std::cin, ip);
	*/

	ServerNetwork server;
	while (true)
	{
		// Move this try/catch into ServerNetwork?
		try
		{
			server.pollEvents();
		}
		catch (int e)
		{
			std::cout << "Server encountered an unknown error from which it couldn't recover." << std::endl;
			std::cout << "Server is shutting down.  Press ENTER to continue.";
			std::string throwaway;
			std::getline(std::cin, throwaway);
			server.cleanup();
		}

		Sleep(20);
	}

	std::cout << "Server is shutting down.  Press ENTER to continue.";
	std::string throwaway;
	std::getline(std::cin, throwaway);
	server.cleanup();
	return 0;
}
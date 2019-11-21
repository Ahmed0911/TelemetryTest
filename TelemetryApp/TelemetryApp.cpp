// TelemetryApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <ws2tcpip.h>

#include "TelemetryHandler.h"

#define SERVER "192.168.0.11"

int main()
{
	std::cout << "TelemetryHandler!\n";

	// Init WS Stuff
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);


	TelemetryHandler telemetry;
	telemetry.create(SERVER);
	for (int i = 0; i != 1000; i++)
	{
		telemetry.run();
	}
	telemetry.destroy();


	WSACleanup();
}
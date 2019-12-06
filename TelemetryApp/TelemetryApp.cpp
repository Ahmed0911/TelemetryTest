// TelemetryApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <ws2tcpip.h>

#include "TelemetryHandler.h"
#include "TestNode.h"

#define SERVER "172.21.20.38"

int main()
{
	std::cout << "TelemetryHandler!\n";

	// Init WS Stuff
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);


	TestNode node{};

	TelemetryHandler telemetry;
	telemetry.create(SERVER);
	//for (int i = 0; i != 1000; i++)
	while (1)
	{
		node.run();

		// get data from node
		node.getTelemetryData(telemetry);

		telemetry.run();
	}
	telemetry.destroy();


	WSACleanup();
}

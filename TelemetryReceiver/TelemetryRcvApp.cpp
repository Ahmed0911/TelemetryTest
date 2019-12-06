// TelemetryReceiver.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <ws2tcpip.h>
#include "TelemetryReceiver.h"

int main()
{
	// Init WS Stuff
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	TelemetryReceiver rcv;

	// receive forever and ever
	while (1)
	{
		rcv.ReceiveData();
	}

	WSACleanup();
}

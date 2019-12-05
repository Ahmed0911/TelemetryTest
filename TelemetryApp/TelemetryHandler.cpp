#include "TelemetryHandler.h"

#if _WIN64
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#define close closesocket
#define MSG_DONTWAIT 0
#else
#include <sys/socket.h>
#endif

constexpr uint32_t TelemetryServerPort = 13000;
constexpr uint32_t TelemetryStreamBuferSize = 1024 * 1024;

void TelemetryHandler::create(std::string serverIP)
{
	// create socket
	_udpSocket = socket(AF_INET, SOCK_DGRAM, 0);
	if (_udpSocket == -1) return; // TODO: throw exception

	// "connect" to server, bind to random port will be done automagically on connect
	sockaddr_in serveraddr{};
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(TelemetryServerPort); // port in server to send data
	serveraddr.sin_addr.s_addr = inet_addr(serverIP.c_str());

	// "connect" to server (use send/write instead of sendto)
	if (connect(_udpSocket, (sockaddr*)&serveraddr, sizeof(serveraddr)) < 0)
	{
		perror("connect failed");
		return;  // TODO: throw exception
	}

	// create stream
	_telemetryStream = std::make_unique<TelemetryStream>(TelemetryStreamBuferSize);
}

void TelemetryHandler::run()
{
	// send data
	if (_udpSocket >= 0)
	{
		// Pack data to send!!
		// TODO



		// send some data
		char buffer[10000];
		int dataToSend = 1000;
		if (send(_udpSocket, buffer, dataToSend, MSG_DONTWAIT) != dataToSend)
		{
			perror("send failed");
		}
	}
}

void TelemetryHandler::destroy()
{
	// close socket
	if (_udpSocket != -1)
	{
		close(_udpSocket);
	}
	// kill stream
	_telemetryStream.reset();
}

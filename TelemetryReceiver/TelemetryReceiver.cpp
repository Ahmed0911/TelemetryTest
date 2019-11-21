#include "TelemetryReceiver.h"

#if _WIN64
#include <winsock2.h>
#define close closesocket
#else
#include <sys/socket.h>
#endif

TelemetryReceiver::TelemetryReceiver()
{
	// create socket
	_udpSocket = socket(AF_INET, SOCK_DGRAM, 0);
	if (_udpSocket == -1)
	{
		perror("socket create failed");
		return;
	}

	// Bind Socket to SERVERPORT
	sockaddr_in localaddr{};
	localaddr.sin_family = AF_INET;
	localaddr.sin_port = htons(SERVERPORT); // listening port
	localaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(_udpSocket, (sockaddr*)&localaddr, sizeof(localaddr)) < 0)
	{
		perror("bind failed");
	}
}

TelemetryReceiver::~TelemetryReceiver()
{
	// close socket
	if (_udpSocket != -1)
	{
		close(_udpSocket);
	}
}

bool TelemetryReceiver::ReceiveData()
{
	// TODO
	return true;
}
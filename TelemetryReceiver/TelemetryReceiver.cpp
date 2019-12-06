#include "TelemetryReceiver.h"
#include <array>
#include <iostream>

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
	std::array<char, 2000> recvBuffer;

	int32_t received = recv(_udpSocket, recvBuffer.data(), 2000, 0);

	// parse data
	if (received > 0)
	{
		int32_t bufferIndex = 0;
		while (bufferIndex < received)
		{
			TelemetryChunkHeader chunk = *reinterpret_cast<TelemetryChunkHeader*>(recvBuffer.data() + bufferIndex);
			bufferIndex += sizeof(TelemetryChunkHeader);

			switch (chunk.objectID)
			{
				case TestNodeDataID:
					if (chunk.index == 0)
					{
						TestNodeData data = *reinterpret_cast<TestNodeData*>(recvBuffer.data() + bufferIndex );
						std::cout << " timestamp: " << data.timestamp;
						std::cout << " frameIndex: " << data.frameIndex;
						std::cout << " height: " << data.height;
						std::cout << " mirko: " << data.mirko;
						std::cout << " slavko: " << data.slavko;
						std::cout << std::endl;
					}
					if (chunk.index == 1)
					{
						TestNodeDataAdd data = *reinterpret_cast<TestNodeDataAdd*>(recvBuffer.data() + bufferIndex);
						std::cout << " dataX: " << data.dataX << std::endl;
					}
					break;
				default:
					std::cout << "Unknown data" << std::endl;
			};

			bufferIndex += chunk.size; // next
		}
	}
	
	return (received > 0);
}
#include "TelemetryReceiver.h"
#include <array>
#include <iostream>
#include "TelemetryDataStructures.h"

#if _WIN64
#include <winsock2.h>
#define close closesocket
#else
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
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

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,0 });
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
				case ApplicationID:
				{
					ApplicationStatistics data = *reinterpret_cast<ApplicationStatistics*>(recvBuffer.data() + bufferIndex);
					std::cout << "-------- Applications ----------" << std::endl;
					std::cout << " mainLoopCounter: " << data.mainLoopCounter << "      " << std::endl;
					std::cout << " mainLoopTimeUS: " << data.mainLoopTimeUS << "      " << std::endl;
					std::cout << " commThreadPeriodUS: " << data.commThreadPeriodUS << "      " << std::endl;
					std::cout << " commThreadTimeUS: " << data.commThreadTimeUS << "      " << std::endl;
					std::cout << std::endl;
					break;
				}
				case TelemetryHandlerID:
				{
					TelemetryHandlerStatistics data = *reinterpret_cast<TelemetryHandlerStatistics*>(recvBuffer.data() + bufferIndex);
					std::cout << "-------- TelemetryHandler ----------" << std::endl;
					std::cout << " sentPackets: " << data.sentPackets << "      " << std::endl;
					std::cout << " totalDataSize: " << data.totalDataSize << "      " << std::endl;
					std::cout << " totalSentToAir: " << data.totalSentToAir << "      " << std::endl;
					std::cout << " failedPackets: " << data.failedPackets << "      " << std::endl;
					std::cout << " totalStoredToDisk: " << data.totalStoredToDisk << "      " << std::endl;
					std::cout << " overSizedChunks: " << data.overSizedChunks << "      " << std::endl;
					std::cout << std::endl;
					break;
				}
				case CameraCaptureID:
				{
					CameraCaptureStatistics data = *reinterpret_cast<CameraCaptureStatistics*>(recvBuffer.data() + bufferIndex);
					std::cout << "-------- CameraCapture ----------" << std::endl;
					std::cout << " completeOutputs: " << data.completeOutputs << "      " << std::endl;
					std::cout << " incompleteOutputs: " << data.incompleteOutputs << "      " << std::endl;
					std::cout << " thrashedOutputs: " << data.thrashedOutputs << "      " << std::endl;
					std::cout << " validFrames: " << data.validFrames << "      " << std::endl;
					std::cout << " desyncFrames: " << data.desyncFrames << "      " << std::endl;
					std::cout << " frameLatencyUS[0]: " << data.frameLatencyUS[0] << "      " << std::endl;
					std::cout << std::endl;
					break;
				}
				case NodePudzaID:
				{
					NodePudzaStatistics data = *reinterpret_cast<NodePudzaStatistics*>(recvBuffer.data() + bufferIndex);
					std::cout << "-------- NodePudza ----------" << std::endl;
					std::cout << " EngineLoadTimeUS: " << data.EngineLoadTimeUS << "      " << std::endl;
					std::cout << " EngineDeserializeTimeUS: " << data.EngineDeserializeTimeUS << "      " << std::endl;
					std::cout << " EngineExecutionTimeUS: " << data.EngineExecutionTimeUS << "      " << std::endl;
					std::cout << std::endl;
					break;
				}
				default:
				{
					std::cout << "-------- Unknown Data ----------" << std::endl;
					std::cout << " Unknown ID: 0x" << std::hex << chunk.objectID << std::dec << " !!!" << std::endl;
					std::cout << std::endl;
					break;
				}
			};

			bufferIndex += chunk.size; // next
		}
	}
	
	return (received > 0);
}

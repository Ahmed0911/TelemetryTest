#include "TelemetryHandler.h"
#include <iostream>

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
	// Send to Wifi/LTE
	sendOverAir();

	// Store localy on disk
	storeToDisk();

	// Empty Buffer
	_statistics.totalDataSize += _telemetryStream->_index;
	_telemetryStream->Clear();
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

void TelemetryHandler::sendOverAir()
{
	// Send Data to socket
	if (_udpSocket >= 0)
	{
		constexpr uint32_t MTU = 1450; // use low value to avoid fragmentation
		uint32_t bufferIndex = 0; // current seek index in stream
		uint32_t sendStartIndex = 0; // index in stream for begining of packet to send
		uint32_t sendSize = 0; // total size of UDP packet to send
		
		do
		{
			// Read Header
			TelemetryChunkHeader chunk = *reinterpret_cast<TelemetryChunkHeader*>(_telemetryStream->_databuffer.get() + bufferIndex);
			uint32_t chunkSize = (sizeof(TelemetryChunkHeader) + chunk.size);

			// Check if there is more room in packet to send
			if ( (sendSize + chunkSize) <= MTU)
			{
				// put more chunks in packet
				sendSize += chunkSize; // send this chunk
				bufferIndex += chunkSize; // advance to next chunk
			}
			else
			{
				// Handle special case - chunk larger than MTU in first chunk to send
				if (sendSize == 0)
				{
					// drop packet
					_statistics.overSizedChunks++;

					bufferIndex += chunkSize; // advance to next chunk	
					sendSize = 0; // send nothing
					sendStartIndex = bufferIndex; // restart									
				}
				else
				{
					char* bufferToSend = reinterpret_cast<char*>(_telemetryStream->_databuffer.get() + bufferIndex);
					if (send(_udpSocket, bufferToSend, sendSize, MSG_DONTWAIT) != sendSize)
					{
						// error
						_statistics.failedPackets++;
						std::cout << "UDP Send Failed: " << std::endl;
					}
					else
					{
						_statistics.sentPackets++;
						_statistics.totalSentToAir += sendSize;
					}

					// reset pointers
					sendStartIndex = bufferIndex; // restart new packet
					sendSize = 0; // reset size
					// do not advance -> this packet could be larger than MTU
				}
			}
		} while (bufferIndex <= _telemetryStream->_index);
	}
}

void TelemetryHandler::storeToDisk()
{
	// TBD
}


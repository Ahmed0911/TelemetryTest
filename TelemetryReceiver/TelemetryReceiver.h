#pragma once
#include <cstdint>
#include <array>
#define SERVERPORT 13000

struct TelemetryChunkHeader
{
	uint32_t objectID;
	uint32_t index;
	uint32_t size; // data size not including header
};

class TelemetryReceiver
{
public:
	TelemetryReceiver();
	~TelemetryReceiver();

	bool ReceiveData();

private:
	int _udpSocket = -1;
	int _udpSocketForwarder = -1;

	void ForwardPacket(std::array<char, 2000>& recvBuffer, uint32_t dataLen);
};

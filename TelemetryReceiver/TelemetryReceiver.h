#pragma once
#include <cstdint>
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
};

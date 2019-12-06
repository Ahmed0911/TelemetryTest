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


// DATA STRUCTS
constexpr uint32_t TestNodeDataID = 0x100;
struct TestNodeData
{
	uint64_t timestamp;
	uint32_t height;
	uint32_t frameIndex;
	uint32_t mirko;
	int64_t slavko;
};

struct TestNodeDataAdd
{
	uint32_t dataX;
};
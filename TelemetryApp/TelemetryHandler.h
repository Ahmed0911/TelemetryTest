#pragma once
#include <string>
#include <memory>
#include "Node.h"

struct TelemetryHandlerStatistics
{
	uint64_t totalDataSize;
	uint64_t totalSentToAir;
	uint64_t totalStoredToDisk;
	uint32_t sentPackets;
	uint32_t failedPackets;
	uint32_t overSizedChunks;
};

class TelemetryHandler
{
public:
	void create(std::string serverIP);
	void run();
	void destroy();

	//TelemetryStream& getStream() { return *_telemetryStream; };
	operator TelemetryStream& () { return *_telemetryStream; };

private:
	int _udpSocket = -1;
	std::unique_ptr<TelemetryStream> _telemetryStream;
	void storeToDisk();
	void sendOverAir();

	TelemetryHandlerStatistics _statistics{};
};

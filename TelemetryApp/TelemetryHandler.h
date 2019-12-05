#pragma once
#include <string>
#include <memory>
#include "Node.h"

class TelemetryHandler
{
public:
	void create(std::string serverIP);
	void run();
	void destroy();

	TelemetryStream& getStream();
	operator TelemetryStream& () { return *_telemetryStream; };

private:
	int _udpSocket = -1;
	std::unique_ptr<TelemetryStream> _telemetryStream;


	//bool addOutput(TelemetryStream& stream);
	// addOutput()
	// storeToDisk()
	// sendToLTE()
};


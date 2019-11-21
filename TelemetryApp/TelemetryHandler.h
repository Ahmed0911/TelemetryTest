#pragma once
#include <string>

#define SERVERPORT 13000

class TelemetryHandler
{
public:
	void create(std::string serverIP);
	void run();
	void destroy();

private:
	int _udpSocket = -1;
	// addOutput()
	// storeToDisk()
	// sendToLTE()
};


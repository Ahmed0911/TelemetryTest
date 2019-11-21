#pragma once

#define SERVERPORT 13000

class TelemetryReceiver
{
public:
	TelemetryReceiver();
	~TelemetryReceiver();

	bool ReceiveData();

private:
	int _udpSocket = -1;
};


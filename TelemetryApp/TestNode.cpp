#include "TestNode.h"
#include <chrono>

void TestNode::create(dwContextHandle_t context, dwSALHandle_t sal)
{

}

void TestNode::run()
{
	// update data - test
	_data.timestamp = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count(); // timestamp in microseconds
	_data.frameIndex++;
	_data.height = 1000;
	_data.mirko = _data.height * 10;
	_data.slavko = -static_cast<int64_t>(_data.height) * 10;

	_data2.dataX = _data.frameIndex*2;
}

void TestNode::destroy()
{

}

void TestNode::getTelemetryData(TelemetryStream& stream)
{
	uint32_t objectID = 0x100; // TBD - make a list somewhere

	stream.writeToBuffer(&_data, sizeof(_data), objectID, 0 );
	stream.writeToBuffer(&_data2, sizeof(_data2), objectID, 1 );
}

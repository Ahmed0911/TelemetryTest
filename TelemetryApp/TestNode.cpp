#include "TestNode.h"

void TestNode::create(dwContextHandle_t context, dwSALHandle_t sal)
{

}

void TestNode::run()
{

}

void TestNode::destroy()
{

}

void TestNode::getTelemetryData(TelemetryStream& stream)
{
	uint32_t size = sizeof(TestNodeTelemetry);
	stream.writeToBuffer(&_telemetry, size);
}
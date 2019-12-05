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
	uint32_t objectID = 0x100; // TBD - make a list somewhere

	stream.writeToBuffer(&_data, sizeof(_data), objectID, 0 );
	stream.writeToBuffer(&_data2, sizeof(_data2), objectID, 1 );
}

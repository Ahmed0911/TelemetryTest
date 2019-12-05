/*
 * Node.h
 *
 *  Created on: Oct 31, 2019
 *      Author: cass
 */

#pragma once
#include <memory>
//#include <dw/core/Context.h>
//#include <dw/sensors/Sensors.h>
typedef int dwContextHandle_t;
typedef int dwSALHandle_t;

class TelemetryHandler;

class TelemetryStream
{
public:
	TelemetryStream(uint32_t bufferSize) : _bufferSize{ bufferSize }, _index{ 0 }
	{
		_databuffer = std::make_unique<uint8_t[]>(_bufferSize);
	}

	bool writeToBuffer(void* ptr, uint32_t size)
	{
		bool writeOk = false;
		if ((_index + size) < _bufferSize)
		{
			memcpy(_databuffer.get(), ptr, size);
			_index += size;

			writeOk = true;
		}

		return writeOk;
	}

private:
	std::unique_ptr<uint8_t[]> _databuffer;
	uint32_t _index;
	uint32_t _bufferSize;

	friend TelemetryHandler;
};

class Node
{
public:
	Node();

	virtual void create(dwContextHandle_t context, dwSALHandle_t sal) = 0;
	virtual void run() = 0 ;
	virtual void destroy() = 0;

	virtual void getTelemetryData(TelemetryStream& stream) = 0;
};

#pragma once
#include <memory>
class TelemetryHandler;

struct TelemetryChunkHeader
{
	uint32_t objectID;
	uint32_t index;
	uint32_t size; // data size not including header
};

class TelemetryStream
{
public:
	TelemetryStream(uint32_t bufferSize) : _bufferSize{ bufferSize }, _index{ 0 }
	{
		_databuffer = std::make_unique<uint8_t[]>(_bufferSize);
	}

	bool writeToBuffer(void* dataPtr, uint32_t size, uint32_t objectID, uint32_t index = 0 )
	{
		bool writeOk = false;

		// TODO: add check with MTU!
		if ((_index + size + sizeof(TelemetryChunkHeader) ) < _bufferSize) // enough space in buffer?
		{
			// write header
			TelemetryChunkHeader hdr{ objectID, index, size };
			std::memcpy(&_databuffer[_index], &hdr, sizeof(TelemetryChunkHeader));
			_index += sizeof(TelemetryChunkHeader);

			// write data
			std::memcpy(&_databuffer[_index], dataPtr, size);
			_index += size;

			writeOk = true;
		}

		return writeOk;
	}

private:
	friend TelemetryHandler;	
	void Clear() { _index = 0; };

	std::unique_ptr<uint8_t[]> _databuffer;
	uint32_t _index;
	uint32_t _bufferSize;

};

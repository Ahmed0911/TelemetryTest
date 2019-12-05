#pragma once
#include "Node.h"

struct TestNodeTelemetry
{
	uint64_t timestamp;
	uint32_t height;
	uint32_t frameIndex;
	uint32_t mirko;
	uint64_t slavko;
};

class TestNode : public Node
{
public:
	TestNode() {};
	void create(dwContextHandle_t context, dwSALHandle_t sal) override;
	void run() override;
	void destroy() override;

	void getTelemetryData(TelemetryStream& stream) override;

private:
	TestNodeTelemetry _telemetry{};
};


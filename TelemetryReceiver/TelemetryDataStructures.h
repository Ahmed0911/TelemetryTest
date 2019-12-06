#pragma once
#include <array>


// Application
constexpr uint32_t ApplicationID = 0x100;
struct ApplicationStatistics
{
	uint64_t mainLoopCounter;
	uint64_t mainLoopTimeUS;
	uint64_t commThreadTimeUS;
	uint64_t commThreadPeriodUS;
};


// Telemetry
constexpr uint32_t TelemetryHandlerID = 0x150;
struct TelemetryHandlerStatistics
{
	uint64_t totalDataSize;
	uint64_t totalSentToAir;
	uint64_t totalStoredToDisk;
	uint32_t sentPackets;
	uint32_t failedPackets;
	uint32_t overSizedChunks;
};


// Camera Capture
constexpr uint32_t CameraCaptureID = 0x200;
constexpr int CAM_CAPTURE_OUTPUT_SIZE = 9;
struct CameraCaptureStatistics
{
	uint64_t completeOutputs; // all cameras acquired
	uint64_t incompleteOutputs; // some cameras are missing
	uint64_t thrashedOutputs; // overwritten inputs that are not consumed

	////////////////////////////////////////////////////////////////////////////////////////////
	///// (T-1).........................(T)...............................(T+1).................
	/////             OLD              VALID         NEARFUTURE           NEXT        DESYNC
	////////////////////////////////////////////////////////////////////////////////////////////
	uint64_t validFrames; // inside active timestamp
	uint64_t nextFrames; // inside next timestamp
	uint64_t oldFrames; // older than active timestamp
	uint64_t nearFutureFrames; // between active and next timestamp
	uint64_t desyncFrames; // frame far in future

	std::array<int64_t, CAM_CAPTURE_OUTPUT_SIZE> frameLatencyUS{}; // Delay from acquisition (readFrame) to frame time-stamp
};


// Node Pudza
constexpr uint32_t NodePudzaID = 0x300;
struct NodePudzaStatistics
{
	uint64_t EngineLoadTimeUS;
	uint64_t EngineDeserializeTimeUS;
	uint64_t EngineExecutionTimeUS;
};


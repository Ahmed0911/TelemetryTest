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

// Sensors Capture
constexpr uint32_t SensorsCaptureID = 0x210;
struct SensorsCaptureStatistics
{
	uint32_t canMessagesRead;
	uint32_t canMessagesProcessed;
	uint32_t canUnknownSignals;
	uint32_t canMessagesSent;
	uint32_t canMessagesFailed;
};
constexpr uint32_t SensorsCaptureDataKiaID = 0x211; // Use "SensorsKiaData" in SensorsCapture.h
constexpr uint32_t SensorsCaptureDataIMUID = 0x212; // Use "SensorsIMUData" in SensorsCapture.h

// Camera Encoder
constexpr uint32_t CameraEncoderID = 0x300;
struct CameraEncoderStatistics
{
	uint32_t feedFrames;
	uint32_t encodedFrames;
	uint32_t encodingErrors;
	uint64_t totalDataSize;
	uint64_t encodingTimeUS;
};
constexpr uint32_t CameraEncoderImageID = 0x300;

// Node AI Driver Analysis
constexpr uint32_t NodeAIDriverAnalysisID = 0x400;
struct NodeAIDriverAnalysisStatistics
{
	uint64_t ExecutionTimeUS;
	uint32_t nbScoreLive;
};

// Node Stereo Vision
constexpr uint32_t NodeStereoVisionID = 0x401;
struct NodeStereoVisionStatistics
{
	uint64_t Rectification_ExecutionTimeUS;
	uint64_t Disparity_ExecutionTimeUS;
};

// Node Scene Classification
constexpr uint32_t NodeSceneClassificationID = 0x402;
struct NodeSceneClassificationStatistics
{
	uint64_t BuildEngine_ExecutionTimeUS;
	uint64_t DataPreparation_ExecutionTimeUS;
	uint64_t Inference_ExecutionTimeUS;
	float32_t timeOfDay[3];
	float32_t roadSurface[3];
	float32_t weather[3];
	float32_t weatherState[3];
};

// Node Motion Planning
constexpr uint32_t NodeMotionPlanningID = 0x403;
struct NodeMotionPlanningStatistics
{
	uint64_t Initialization_ExecutionTimeUS;
	uint64_t ExecutionTimeUS;
};

// Node Structure From Motion
constexpr uint32_t NodeSFMID = 0x404;
struct NodeSFMStatistics
{
	uint64_t overal_ExecutionTimeUS;
	uint64_t tracking_ExecutionTimeUS;
};


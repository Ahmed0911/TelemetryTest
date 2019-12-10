#include "TelemetryReceiver.h"
#include <array>
#include <iostream>
typedef float  float32_t;
typedef double float64_t;
#include "TelemetryDataStructures.h"

#if _WIN64
#include <winsock2.h>
#define close closesocket
#else
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#endif

TelemetryReceiver::TelemetryReceiver()
{
	// create socket
	_udpSocket = socket(AF_INET, SOCK_DGRAM, 0);
	if (_udpSocket == -1)
	{
		perror("socket create failed");
		return;
	}

	// Bind Socket to SERVERPORT
	sockaddr_in localaddr{};
	localaddr.sin_family = AF_INET;
	localaddr.sin_port = htons(SERVERPORT); // listening port
	localaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(_udpSocket, (sockaddr*)&localaddr, sizeof(localaddr)) < 0)
	{
		perror("bind failed");
	}
}

TelemetryReceiver::~TelemetryReceiver()
{
	// close socket
	if (_udpSocket != -1)
	{
		close(_udpSocket);
	}
}

bool TelemetryReceiver::ReceiveData()
{
	std::array<char, 2000> recvBuffer;

	int32_t received = recv(_udpSocket, recvBuffer.data(), 2000, 0);

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,0 });
	// parse data
	if (received > 0)
	{
		int32_t bufferIndex = 0;
		while (bufferIndex < received)
		{
			TelemetryChunkHeader chunk = *reinterpret_cast<TelemetryChunkHeader*>(recvBuffer.data() + bufferIndex);
			bufferIndex += sizeof(TelemetryChunkHeader);

			switch (chunk.objectID)
			{
				case ApplicationID:
				{
					ApplicationStatistics data = *reinterpret_cast<ApplicationStatistics*>(recvBuffer.data() + bufferIndex);
					std::cout << "-------- Application ----------" << std::endl;
					std::cout << " mainLoopCounter: " << data.mainLoopCounter << "      " << std::endl;
					std::cout << " mainLoopTimeUS: " << data.mainLoopTimeUS << "      " << std::endl;
					std::cout << " commThreadPeriodUS: " << data.commThreadPeriodUS << "      " << std::endl;
					std::cout << " commThreadTimeUS: " << data.commThreadTimeUS << "      " << std::endl;
					std::cout << std::endl;
					break;
				}
				case TelemetryHandlerID:
				{
					TelemetryHandlerStatistics data = *reinterpret_cast<TelemetryHandlerStatistics*>(recvBuffer.data() + bufferIndex);
					std::cout << "-------- TelemetryHandler ----------" << std::endl;
					std::cout << " sentPackets: " << data.sentPackets << "      " << std::endl;
					std::cout << " totalDataSize: " << data.totalDataSize << "      " << std::endl;
					std::cout << " totalSentToAir: " << data.totalSentToAir << "      " << std::endl;
					std::cout << " failedPackets: " << data.failedPackets << "      " << std::endl;
					std::cout << " totalStoredToDisk: " << data.totalStoredToDisk << "      " << std::endl;
					std::cout << " overSizedChunks: " << data.overSizedChunks << "      " << std::endl;
					std::cout << std::endl;
					break;
				}
				case CameraCaptureID:
				{
					CameraCaptureStatistics data = *reinterpret_cast<CameraCaptureStatistics*>(recvBuffer.data() + bufferIndex);
					std::cout << "-------- CameraCapture ----------" << std::endl;
					std::cout << " completeOutputs: " << data.completeOutputs << "      " << std::endl;
					std::cout << " incompleteOutputs: " << data.incompleteOutputs << "      " << std::endl;
					std::cout << " thrashedOutputs: " << data.thrashedOutputs << "      " << std::endl;
					std::cout << " validFrames: " << data.validFrames << "      " << std::endl;
					std::cout << " desyncFrames: " << data.desyncFrames << "      " << std::endl;
					std::cout << " frameLatencyUS[0]: " << data.frameLatencyUS[0] << "      " << std::endl;
					std::cout << std::endl;
					break;
				}
				case NodePudzaID:
				{
					NodePudzaStatistics data = *reinterpret_cast<NodePudzaStatistics*>(recvBuffer.data() + bufferIndex);
					std::cout << "-------- NodePudza ----------" << std::endl;
					std::cout << " EngineLoadTimeUS: " << data.EngineLoadTimeUS << "      " << std::endl;
					std::cout << " EngineDeserializeTimeUS: " << data.EngineDeserializeTimeUS << "      " << std::endl;
					std::cout << " EngineExecutionTimeUS: " << data.EngineExecutionTimeUS << "      " << std::endl;
					std::cout << std::endl;
					break;
				}
				case NodeAIDriverAnalysisID:
				{
					NodeAIDriverAnalysisStatistics data = *reinterpret_cast<NodeAIDriverAnalysisStatistics*>(recvBuffer.data() + bufferIndex);
					std::cout << "-------- NodeAIDriverAnalysis ----------" << std::endl;
					std::cout << " ExecutionTimeUS: " << data.ExecutionTimeUS << "      " << std::endl;
					std::cout << " nbScoreLive: " << data.nbScoreLive << "      " << std::endl;
					std::cout << std::endl;
					break;
				}
				case NodeStereoVisionID:
				{
					NodeStereoVisionStatistics data = *reinterpret_cast<NodeStereoVisionStatistics*>(recvBuffer.data() + bufferIndex);
					std::cout << "-------- NodeStereoVision ----------" << std::endl;
					std::cout << " Rectification_ExecutionTimeUS: " << data.Rectification_ExecutionTimeUS << "      " << std::endl;
					std::cout << " Disparity_ExecutionTimeUS: " << data.Disparity_ExecutionTimeUS << "      " << std::endl;
					std::cout << std::endl;
					break;
				}
				case NodeSceneClassificationID:
				{
					NodeSceneClassificationStatistics data = *reinterpret_cast<NodeSceneClassificationStatistics*>(recvBuffer.data() + bufferIndex);
					std::cout << "-------- NodeSceneClassification ----------" << std::endl;
					std::cout << " BuildEngine_ExecutionTimeUS: " << data.BuildEngine_ExecutionTimeUS << "      " << std::endl;
					std::cout << " DataPreparation_ExecutionTimeUS: " << data.DataPreparation_ExecutionTimeUS << "      " << std::endl;
					std::cout << " Inference_ExecutionTimeUS: " << data.Inference_ExecutionTimeUS << "      " << std::endl;
					std::cout << " timeOfDay: " << data.timeOfDay[0] << "/" << data.timeOfDay[1] << "/" << data.timeOfDay[2] << "      " << std::endl;
					std::cout << " roadSurface: " << data.roadSurface[0] << "/" << data.roadSurface[1] << "/" << data.roadSurface[2] << "      " << std::endl;
					std::cout << " weather: " << data.weather[0] << "/" << data.weather[1] << "/" << data.weather[2] << "      " << std::endl;
					std::cout << " weatherState: " << data.weatherState[0] << "/" << data.weatherState[1] << "/" << data.weatherState[2] << "      " << std::endl;
					std::cout << std::endl;
					break;
				}
				case NodeMotionPlanningID:
				{
					NodeMotionPlanningStatistics data = *reinterpret_cast<NodeMotionPlanningStatistics*>(recvBuffer.data() + bufferIndex);
					std::cout << "-------- NodeMotionPlanning ----------" << std::endl;
					std::cout << " Initialization_ExecutionTimeUS: " << data.Initialization_ExecutionTimeUS << "      " << std::endl;
					std::cout << " ExecutionTimeUS: " << data.ExecutionTimeUS << "      " << std::endl;
					std::cout << std::endl;
					break;
				}
				case NodeSFMID:
				{
					NodeSFMStatistics data = *reinterpret_cast<NodeSFMStatistics*>(recvBuffer.data() + bufferIndex);
					std::cout << "-------- NodeSFM ----------" << std::endl;
					std::cout << " overal_ExecutionTimeUS: " << data.overal_ExecutionTimeUS << "      " << std::endl;
					std::cout << " tracking_ExecutionTimeUS: " << data.tracking_ExecutionTimeUS << "      " << std::endl;
					std::cout << std::endl;
					break;
				}
				default:
				{
					std::cout << "-------- Unknown Data ----------" << std::endl;
					std::cout << " Unknown ID: 0x" << std::hex << chunk.objectID << std::dec << " !!!" << std::endl;
					std::cout << std::endl;
					break;
				}
			};

			bufferIndex += chunk.size; // next
		}
	}
	
	return (received > 0);
}

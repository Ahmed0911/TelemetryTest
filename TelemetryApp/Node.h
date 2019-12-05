/*
 * Node.h
 *
 *  Created on: Oct 31, 2019
 *      Author: cass
 */

#pragma once
//#include <dw/core/Context.h>
//#include <dw/sensors/Sensors.h>
typedef int dwContextHandle_t;
typedef int dwSALHandle_t;

#include "TelemetryStream.h"

class Node
{
public:
	Node();

	virtual void create(dwContextHandle_t context, dwSALHandle_t sal) = 0;
	virtual void run() = 0 ;
	virtual void destroy() = 0;

	virtual void getTelemetryData(TelemetryStream& stream) = 0;
};

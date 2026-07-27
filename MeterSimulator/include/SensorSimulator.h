#ifndef SENSOR_SIMULATOR_H
#define SENSOR_SIMULATOR_H

#include "TelemetryData.h"

class SensorSimulator
{
public:
    SensorSimulator();

    TelemetryData generateTelemetryPacket();

private:
    unsigned int sequenceNumber;
};

#endif
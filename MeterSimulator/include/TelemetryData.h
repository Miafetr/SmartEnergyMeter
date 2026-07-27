#ifndef TELEMETRY_DATA_H
#define TELEMETRY_DATA_H

#include <string>

enum class DeviceStatus
{
    Online,
    Warning,
    Fault
};

struct TelemetryData
{
    // Identification
    std::string deviceId;
    std::string timestamp;
    unsigned int sequenceNumber;

    //Electrical Measurements
    double voltage;
    double current;
    double power;
    double temperature;

    //Device Status
    DeviceStatus status;
};

#endif
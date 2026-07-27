#ifndef SMART_METER_H
#define SMART_METER_H

#include <string>

#include "SensorSimulator.h"
#include "TcpClient.h"

class SmartMeter
{
public:
    SmartMeter(const std::string& deviceId);

    void run();

private:
    std::string deviceId;

    SensorSimulator simulator;
    TcpClient client;
};

#endif
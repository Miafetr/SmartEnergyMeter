#ifndef SMART_METER_H
#define SMART_METER_H

#include "SensorSimulator.h"
#include "TcpClient.h"

class SmartMeter
{
public:
    SmartMeter();

    void start();

private:
    SensorSimulator simulator;
    TcpClient client;
};

#endif
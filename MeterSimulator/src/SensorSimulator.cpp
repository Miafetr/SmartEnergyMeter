#include "SensorSimulator.h"
#include <random>

SensorSimulator::SensorSimulator()
{
    sequenceNumber = 1;
}

TelemetryData SensorSimulator::generateTelemetryPacket()
{
    // Create the random-number system only once.
    static std::random_device rd;
    static std::mt19937 gen(rd());

    // Define realistic measurement ranges.
    static std::uniform_real_distribution<double> voltageDistribution(118.0, 122.0);
    static std::uniform_real_distribution<double> currentDistribution(5.0, 15.0);
    static std::uniform_real_distribution<double> temperatureDistribution(20.0, 60.0);

    TelemetryData packet;

    packet.deviceId = "Meter-001";
    packet.timestamp = "2026-07-27 10:15:00";

    packet.sequenceNumber = sequenceNumber;
    sequenceNumber++;

    packet.voltage = voltageDistribution(gen);
    packet.current = currentDistribution(gen);

    // Electrical power = voltage × current.
    packet.power = packet.voltage * packet.current;

    packet.temperature = temperatureDistribution(gen);

    // Determine the device status from its measurements.
    if (packet.temperature >= 58.0)
    {
        packet.status = DeviceStatus::Fault;
    }
    else if (packet.temperature >= 50.0)
    {
        packet.status = DeviceStatus::Warning;
    }
    else
    {
        packet.status = DeviceStatus::Online;
    }

    return packet;
}
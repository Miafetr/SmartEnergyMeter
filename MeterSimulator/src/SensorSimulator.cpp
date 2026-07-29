#include "SensorSimulator.h"

#include <chrono>
#include <ctime>
#include <iomanip>
#include <random>
#include <sstream>
#include <iostream>

namespace
{
    std::string getCurrentTimestamp()
    {
        const auto now = std::chrono::system_clock::now();
        const std::time_t currentTime =
            std::chrono::system_clock::to_time_t(now);

        std::tm localTime{};
        localtime_r(&currentTime, &localTime);

        std::ostringstream timestampStream;

        timestampStream << std::put_time(
            &localTime,
            "%Y-%m-%d %H:%M:%S"
        );

        return timestampStream.str();
    }
}

SensorSimulator::SensorSimulator()
    : sequenceNumber(1)
{
}

TelemetryData SensorSimulator::generateTelemetryPacket()
{
    // Create the random-number generator only once.
static std::mt19937 generator(
    static_cast<unsigned int>(
        std::chrono::steady_clock::now()
            .time_since_epoch()
            .count()
    )
);

    // Define realistic electrical measurement ranges.
    static std::uniform_real_distribution<double>
        voltageDistribution(118.0, 122.0);

    static std::uniform_real_distribution<double>
        currentDistribution(0.5, 15.0);

    static std::uniform_real_distribution<double>
        temperatureNoiseDistribution(-2.0, 8.0);

    TelemetryData packet;

    packet.dev
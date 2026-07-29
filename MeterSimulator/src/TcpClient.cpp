#include "TcpClient.h"

#include <iomanip>
#include <iostream>

TcpClient::TcpClient()
{
    connected = false;
}

bool TcpClient::connect(const std::string& ipAddress, int port)
{
    connected = true;
    return true;
}

bool TcpClient::sendTelemetry(const TelemetryData& packet)
{
    if (!connected)
    {
        return false;
    }

    std::cout << std::fixed << std::setprecision(2);

    std::cout << "\n========================================\n";
    std::cout << "       Smart Meter Telemetry Packet\n";
    std::cout << "========================================\n";

    std::cout << "Device ID       : "
              << packet.deviceId << '\n';

    std::cout << "Timestamp       : "
              << packet.timestamp << '\n';

    std::cout << "Sequence Number : "
              << packet.sequenceNumber << '\n';

    std::cout << "Voltage         : "
              << packet.voltage << " V\n";

    std::cout << "Current         : "
              << packet.current << " A\n";

    std::cout << "Power           : "
              << packet.power << " W\n";

    std::cout << "Temperature     : "
              << packet.temperature << " C\n";

    std::cout << "Status          : ";

    switch (packet.status)
    {
        case DeviceStatus::Online:
            std::cout << "Online";
            break;

        case DeviceStatus::Warning:
            std::cout << "Warning";
            break;

        case DeviceStatus::Fault:
            std::cout << "Fault";
            break;
    }

    std::cout << "\n========================================\n";

    return true;
}

void TcpClient::disconnect()
{
    connected = false;
}
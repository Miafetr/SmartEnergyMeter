#include "TcpClient.h"

#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#include <iomanip>
#include <iostream>

TcpClient::TcpClient()
{
    socketDescriptor = -1;
    connected = false;
}

bool TcpClient::connect(const std::string& ipAddress, int port)
{
    socketDescriptor = socket(AF_INET, SOCK_STREAM, 0);

    if (socketDescriptor < 0)
    {
        std::cerr << "Failed to create socket.\n";
        return false;
    }

    sockaddr_in serverAddress{};

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);

    int addressResult = inet_pton(
        AF_INET,
        ipAddress.c_str(),
        &serverAddress.sin_addr
    );

    if (addressResult <= 0)
    {
        std::cerr << "Invalid IP address.\n";
        close(socketDescriptor);
        socketDescriptor = -1;
        return false;
    }

    int connectionResult = ::connect(
        socketDescriptor,
        reinterpret_cast<sockaddr*>(&serverAddress),
        sizeof(serverAddress)
    );

    if (connectionResult < 0)
    {
        std::cerr << "Failed to connect to backend.\n";
        close(socketDescriptor);
        socketDescriptor = -1;
        return false;
    }

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
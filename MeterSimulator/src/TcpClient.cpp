#include "TcpClient.h"

#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

namespace
{
    std::string statusToString(DeviceStatus status)
    {
        switch (status)
        {
            case DeviceStatus::Online:
                return "Online";

            case DeviceStatus::Warning:
                return "Warning";

            case DeviceStatus::Fault:
                return "Fault";
        }

        return "Unknown";
    }
}

TcpClient::TcpClient()
{
    socketDescriptor = -1;
    connected = false;
}

bool TcpClient::connect(
    const std::string& ipAddress,
    int port
)
{
    socketDescriptor = socket(
        AF_INET,
        SOCK_STREAM,
        0
    );

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
        reinterpret_cast<sockaddr*>(
            &serverAddress
        ),
        sizeof(serverAddress)
    );

    if (connectionResult < 0)
    {
        std::cerr
            << "Failed to connect to backend.\n";

        close(socketDescriptor);
        socketDescriptor = -1;

        return false;
    }

    connected = true;
    return true;
}

bool TcpClient::sendTelemetry(
    const TelemetryData& packet
)
{
    if (!connected)
    {
        return false;
    }

    std::ostringstream jsonStream;

    jsonStream
        << std::fixed
        << std::setprecision(2)
        << "{"
        << "\"deviceId\":\""
        << packet.deviceId
        << "\","
        << "\"timestamp\":\""
        << packet.timestamp
        << "\","
        << "\"sequenceNumber\":"
        << packet.sequenceNumber
        << ","
        << "\"voltage\":"
        << packet.voltage
        << ","
        << "\"current\":"
        << packet.current
        << ","
        << "\"power\":"
        << packet.power
        << ","
        << "\"temperature\":"
        << packet.temperature
        << ","
        << "\"status\":\""
        << statusToString(packet.status)
        << "\""
        << "}\n";

    std::string jsonPacket = jsonStream.str();

    std::size_t totalBytesSent = 0;

    while (totalBytesSent < jsonPacket.size())
    {
        ssize_t bytesSent = ::send(
            socketDescriptor,
            jsonPacket.data() + totalBytesSent,
            jsonPacket.size() - totalBytesSent,
            0
        );

        if (bytesSent <= 0)
        {
            std::cerr
                << "Failed to send telemetry.\n";

            connected = false;
            return false;
        }

        totalBytesSent +=
            static_cast<std::size_t>(bytesSent);
    }

    std::cout << std::fixed
              << std::setprecision(2);

    std::cout
        << "\n========================================\n"
        << "       Smart Meter Telemetry Packet\n"
        << "========================================\n"
        << "Device ID       : "
        << packet.deviceId << '\n'
        << "Timestamp       : "
        << packet.timestamp << '\n'
        << "Sequence Number : "
        << packet.sequenceNumber << '\n'
        << "Voltage         : "
        << packet.voltage << " V\n"
        << "Current         : "
        << packet.current << " A\n"
        << "Power           : "
        << packet.power << " W\n"
        << "Temperature     : "
        << packet.temperature << " C\n"
        << "Status          : "
        << statusToString(packet.status)
        << '\n'
        << "========================================\n";

    return true;
}

void TcpClient::disconnect()
{
    if (socketDescriptor >= 0)
    {
        close(socketDescriptor);
        socketDescriptor = -1;
    }

    connected = false;
}
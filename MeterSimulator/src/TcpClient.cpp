#include "TcpClient.h"

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

    return true;
}

void TcpClient::disconnect()
{
    connected = false;
}
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
    // (connected) is more efficient than (connected == true). Also (!connected) is more efficient than (connected == false).
    if (connected)
    {
        return true;
    }
    return false;
}

void TcpClient::disconnect()
{
    connected = false;
}
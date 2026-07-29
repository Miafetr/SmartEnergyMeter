#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

#include <string>
#include "TelemetryData.h"

class TcpClient
{
public:
    TcpClient();

    // C++ Best Practice:
    // - const = function cannot modify the object.
    // - & = pass by reference (no copy).
    // - const Type& = efficient and safe for read-only objects.
    bool connect(const std::string& ipAddress, int port);

    bool sendTelemetry(const TelemetryData& packet);


    void disconnect();

private:
    bool connected;
};

#endif
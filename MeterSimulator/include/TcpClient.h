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
    // - const Type& = ef
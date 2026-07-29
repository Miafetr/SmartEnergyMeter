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
       
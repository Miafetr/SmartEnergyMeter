#include "SmartMeter.h"

#include <chrono>
#include <iostream>
#include <thread>

SmartMeter::SmartMeter()
{
}

void SmartMeter::start()
{
    bool connectedSuccessfully =
        client.connect("127.0.0.1", 5000);

    if (!connectedSuccessfully)
    {
        std::cerr << "Failed to connect to the backend.\n";
        return;
    }

    std::cout << "Smart meter connected successfully.\n";

    for (int packetCount = 0; packetCount < 10; packetCount++)
    {
        TelemetryData packet =
            simulator.generateTelemetryPacket();

        bool sentSuccessfully =
            client.sendTelemetry(packet);

        if (sentSuccessfully)
        {
            std::cout
                << "Packet sent successfully. Sequence number: "
                << packet.sequenceNumber
                << '\n';
        }
        else
        {
            std::cerr
                << "Failed to send packet. Sequence number: "
                << packet.sequenceNumber
                << '\n';
        }

        std::this_thread::sleep_for(
            std::chrono::seconds(1)
        );
    }

    client.disconnect();

    std::cout << "Smart meter disconnected.\n";
}
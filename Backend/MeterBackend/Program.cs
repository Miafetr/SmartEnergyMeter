using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Text.Json;
using MeterBackend;

TcpListener server = new TcpListener(
    IPAddress.Loopback,
    5000
);

server.Start();

Console.WriteLine("Meter backend is running.");
Console.WriteLine("Waiting for the meter to connect...");

TcpClient client = await server.AcceptTcpClientAsync();

Console.WriteLine("Meter connected.");
Console.WriteLine();

using NetworkStream networkStream = client.GetStream();

using StreamReader reader = new StreamReader(
    networkStream,
    Encoding.UTF8
);

JsonSerializerOptions jsonOptions = new JsonSerializerOptions
{
    PropertyNameCaseInsensitive = true
};

while (true)
{
    string? jsonPacket = await reader.ReadLineAsync();

    if (jsonPacket == null)
    {
        break;
    }

    TelemetryData? telemetry =
        JsonSerializer.Deserialize<TelemetryData>(
            jsonPacket,
            jsonOptions
        );

    if (telemetry == null)
    {
        Console.WriteLine("Invalid telemetry packet.");
        continue;
    }

    Console.WriteLine("Telemetry object created:");
    Console.WriteLine($"Device ID: {telemetry.DeviceId}");
    Console.WriteLine($"Timestamp: {telemetry.Timestamp}");
    Console.WriteLine($"Sequence: {telemetry.SequenceNumber}");
    Console.WriteLine($"Voltage: {telemetry.Voltage:F2} V");
    Console.WriteLine($"Current: {telemetry.Current:F2} A");
    Console.WriteLine($"Power: {telemetry.Power:F2} W");
    Console.WriteLine($"Temperature: {telemetry.Temperature:F2} C");
    Console.WriteLine($"Status: {telemetry.Status}");
    Console.WriteLine();
}

client.Close();
server.Stop();

Console.WriteLine("Meter disconnected.");
Console.WriteLine("Backend stopped.");
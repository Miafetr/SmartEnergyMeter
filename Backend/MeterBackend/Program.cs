using System.Net;
using System.Net.Sockets;
using System.Text;

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

while (true)
{
    string? jsonPacket = await reader.ReadLineAsync();

    if (jsonPacket == null)
    {
        break;
    }

    Console.WriteLine("Telemetry received:");
    Console.WriteLine(jsonPacket);
    Console.WriteLine();
}

client.Close();
server.Stop();

Console.WriteLine("Meter disconnected.");
Console.WriteLine("Backend stopped.");
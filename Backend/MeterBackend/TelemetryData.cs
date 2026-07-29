namespace MeterBackend;

public class TelemetryData
{
    public string DeviceId { get; set; } = "";

    public string Timestamp { get; set; } = "";

    public uint SequenceNumber { get; set; }

    public double Voltage { get; set; }

    public double Current { get; set; }

    public double Power { get; set; }

    public double Temperature { get; set; }

    public string Status { get; set; } = "";
}
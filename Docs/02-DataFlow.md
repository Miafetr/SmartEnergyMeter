# Data Flow

SensorSimulator.cpp
        │
        ▼
Generate TelemetryData
        │
        ▼
SmartMeter.cpp
        │
        ▼
TcpClient.cpp
        │
        ▼
Serialize to JSON
        │
        ▼
TCP Socket
        │
        ▼
Program.cs
        │
        ▼
Deserialize JSON
        │
        ▼
TelemetryData.cs
        │
        ▼
Backend Processing

---

## One Telemetry Packet Contains

- Device ID
- Timestamp
- Sequence Number
- Voltage
- Current
- Power
- Temperature
- Status

---

## Communication

Client
↓

TCP Socket

↓

Server

↓

JSON

↓

C# Object
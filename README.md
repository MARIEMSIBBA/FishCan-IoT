# FishCan IoT — Intelligent Monitoring System for Fish Canning Production

> An intelligent IoT system for real-time monitoring and control of fish canning production processes, with automatic anomaly detection and AI-based prediction.



##  Context

The food industry, particularly fish canning production, relies on two critical processes that directly determine food safety and product quality:

- **Seaming** — the mechanical operation that hermetically seals cans. Any seaming defect compromises product integrity and can lead to serious bacterial contamination.

- **Thermal Sterilization** — ensures the elimination of pathogenic microorganisms, notably *Clostridium botulinum*, responsible for botulism. It is quantified by the **F0 lethality value**, which represents the equivalent thermal treatment time at **121.1°C**.

**FishCan IoT** was developed to intelligently monitor both processes in real time using industrial sensors, automatically detect anomalies, and transmit data to an AI-powered analytics platform.

---

## Project Objectives

1. **Real-Time Data Collection** — Acquire data from simulated industrial sensors (temperature, seaming torque, vibration) using ESP32.
2. **Sterilization Monitoring** — Continuously calculate the F0 lethality value to guarantee food safety compliance.
3. **Automatic Anomaly Detection** — Identify seaming defects and non-compliant sterilization conditions instantly.
4. **Data Transmission** — Send collected data to a FastAPI server via HTTP protocol for storage and processing.
5. **Real-Time Visualization** — Display live process data through an interactive dashboard.
6. **AI-Based Prediction** — Exploit historical data through Machine Learning models to predict anomalies and improve the industrial process.

---

## Key Features

✔️ Real-Time Sensor Data Acquisition via ESP32  
✔️ F0 Lethality Value Calculation & Sterilization Monitoring  
✔️ Automatic Anomaly Detection (Seaming & Sterilization)  
✔️ HTTP Data Transmission to FastAPI Backend (HTTP 200)  
✔️ Interactive Real-Time Dashboard  
✔️ AI-Powered Anomaly Prediction  
✔️ Modular & Scalable Architecture  

---

## System Architecture

```text
┌─────────────────────────────────────────────────┐
│           Industrial Sensors (Simulated)         │
│     Temperature | Seaming Torque | Vibration     │
└──────────────────────┬──────────────────────────┘
                       ↓
┌──────────────────────────────────────────────────┐
│              ESP32 Microcontroller                │
│        Data Acquisition + HTTP Transmission       │
│              Serial Output (115200 baud)          │
└──────────────────────┬───────────────────────────┘
                       ↓  HTTP POST (200 OK)
┌──────────────────────────────────────────────────┐
│              FastAPI Backend Server               │
│           Data Storage & Processing               │
└──────────┬───────────────────────┬───────────────┘
           ↓                       ↓
┌─────────────────┐     ┌─────────────────────────┐
│    Dashboard    │     │      AI / ML Models      │
│ Real-Time View  │     │   Anomaly Prediction     │
└─────────────────┘     └─────────────────────────┘
```

---

## Technologies Used

| Category | Technologies |
|---|---|
| Embedded System | ESP32, Arduino IDE |
| Communication | HTTP POST |
| Sensors | Temperature, Seaming Torque, Vibration |
| Backend | FastAPI, Uvicorn |
| Machine Learning | Scikit-learn, Pandas, NumPy |
| Visualization | Web Dashboard |
| Languages | Python, C++ (ESP32 Firmware) |

---

##  Project Structure

```bash
fishcan-iot/
│
├── main.cpp                  # ESP32 firmware (sensor reading + HTTP send)
│
├── api.py                    # FastAPI server
│
│
├── sensor_data.csv           # Historical sensor data
│ 
│
├── README.md
└── .gitignore
```

---

## Installation

### 1️⃣ Clone the Repository

```bash
git clone https://github.com/MARIEMSIBBA/fishcan-iot.git
cd fishcan-iot
```

### 2️⃣ Flash ESP32 Firmware

- Open `main.cpp` in **Arduino IDE**
- Select board: **ESP32 Dev Module**
- Configure your WiFi credentials:
```cpp
const char* ssid     = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
```
- Upload the firmware to the board

---

## Running the Project

### Start the API Server

```bash
uvicorn api.api:app --reload
```

### Access Swagger Documentation

```
http://127.0.0.1:8000/docs
```


## Real Data Sample

### ESP32 Serial Monitor Output

```
WiFi OK
====== DATA ======
Temp:        110.69 °C
Torque:        5.00 N·m
Vibration:     1.01 m/s²
F0:            0.00 min
Seaming:       ANOMALY
Sterilization: ANOMALY
HTTP:          200
==================
```

### CSV Sensor Data

```csv
Temperature, Torque, Vibration, F0,      Seaming, Sterilization
110.69,      8.15,   0.93,      0.003,   NORMAL,  ANOMALY
110.69,      8.15,   1.50,      0.006,   NORMAL,  ANOMALY
117.35,      8.15,   1.55,      0.029,   ANOMALY, NORMAL
112.03,      10.19,  0.49,      0.061,   NORMAL,  NORMAL
110.02,      17.00,  1.26,      0.003,   ANOMALY, ANOMALY
```

---

## Monitored Parameters

| Parameter | Description | Unit | Safety Threshold |
|---|---|---|---|
| Temperature | Sterilization process temperature | °C | ≥ 121.1°C |
| F0 Value | Lethality value at 121.1°C | min | ≥ 3 min |
| Seaming Torque | Mechanical closing force | N·m | 8 – 15 N·m |
| Vibration | Machine vibration level | m/s² | < 1.5 m/s² |

---

## Applications

- Fish & Food Canning Industrial Plants
- Food Safety Compliance Monitoring
- IoT-Based Industrial Predictive Maintenance
- Embedded AI for Production Quality Control

---

## Future Improvements

- [ ] MQTT Protocol Integration
- [ ] Cloud Deployment (AWS / Azure)
- [ ] Mobile Push Alert Notifications
- [ ] Docker Containerization
- [ ] Deep Learning Models (LSTM for time-series)
- [ ] Multi-Line Production Monitoring

---

## Author

**Sibba Mariem**  
Master's Student — Computer Engineering & Embedded Systems  
Ibn Zohr University, Agadir, Morocco

[![LinkedIn](https://img.shields.io/badge/LinkedIn-SIBBAMARIEM-blue?logo=linkedin)](https://www.linkedin.com/in/SIBBAMARIEM/)
[![Email](https://img.shields.io/badge/Email-mariemsibba6@gmail.com-red?logo=gmail)](mailto:mariemsibba6@gmail.com)

---

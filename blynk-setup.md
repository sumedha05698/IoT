# Blynk Dashboard Setup Guide

## 1. Create a New Template
- Open the [Blynk Console](https://blynk.cloud)
- Click **+ New Template**
- Name: `LED PROJECT`
- Hardware: `ESP32`
- Connection: `WiFi`

---

## 2. Datastreams (Virtual Pins)

| Virtual Pin | Name              | Type    | Data Type | Range  |
|-------------|-------------------|---------|-----------|--------|
| V0          | Red LED           | Integer | 0–1       | Button |
| V1          | Yellow LED        | Integer | 0–1       | Button |
| V2          | Green LED         | Integer | 0–1       | Button |
| V3          | Blue LED          | Integer | 0–1       | Button |
| V4          | Temperature       | Double  | –40–80    | Gauge  |
| V5          | Humidity          | Double  | 0–100     | Gauge  |
| V6          | All LEDs (Master) | Integer | 0–1       | Button |
| V7          | Red Status        | Integer | 0–1       | LED    |
| V8          | Yellow Status     | Integer | 0–1       | LED    |
| V9          | Green Status      | Integer | 0–1       | LED    |
| V10         | Blue Status       | Integer | 0–1       | LED    |
| V11         | Heat Index        | Double  | –40–80    | Gauge  |

---

## 3. Dashboard Widgets

### Control Widgets
| Widget  | Linked Pin | Label         |
|---------|-----------|---------------|
| Button  | V0        | Red LED       |
| Button  | V1        | Yellow LED    |
| Button  | V2        | Green LED     |
| Button  | V3        | Blue LED      |
| Button  | V6        | ALL LEDs      |

### Status Indicators
| Widget    | Linked Pin | Label          |
|-----------|-----------|----------------|
| LED       | V7        | 🔴 Red Status  |
| LED       | V8        | 🟡 Yellow Status|
| LED       | V9        | 🟢 Green Status |
| LED       | V10       | 🔵 Blue Status  |

### Sensor Widgets
| Widget  | Linked Pin | Label         | Color  |
|---------|-----------|---------------|--------|
| Gauge   | V4        | Temperature   | Orange |
| Gauge   | V5        | Humidity      | Blue   |
| Gauge   | V11       | Heat Index    | Red    |
| Chart   | V4, V5    | Sensor History| -      |

---

## 4. Get Auth Token
- Go to your Template → **Devices** → **+ New Device**
- Copy the `BLYNK_AUTH_TOKEN` and paste it in `main.ino`

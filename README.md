# 💡 IoT-Based Multi-LED Control & Environmental Monitoring System

<p align="center">
  <img src="https://img.shields.io/badge/Platform-ESP32-blue?style=for-the-badge&logo=espressif" />
  <img src="https://img.shields.io/badge/IoT-Blynk-00C8FF?style=for-the-badge" />
  <img src="https://img.shields.io/badge/Sensor-DHT22-green?style=for-the-badge" />
  <img src="https://img.shields.io/badge/Simulation-Wokwi-9B59B6?style=for-the-badge" />
  <img src="https://img.shields.io/badge/Status-Active-brightgreen?style=for-the-badge" />
</p>

<p align="center">
  Control multiple LEDs remotely from your smartphone and monitor real-time temperature & humidity — all over WiFi using the ESP32 and Blynk IoT platform.
</p>

---

## 📸 Demo

> 🔗 **[Live Simulation on Wokwi](https://wokwi.com/projects/443963082483615745)**

---

## ✨ Features

| Feature | Description |
|--------|-------------|
| 🔴🟡🟢🔵 Individual LED Control | Toggle each LED independently from the Blynk app |
| 🔦 Master Toggle | Turn ALL LEDs ON or OFF with a single tap |
| 🌡️ Temperature Monitoring | Real-time DHT22 temperature readings (°C) |
| 💧 Humidity Monitoring | Live relative humidity readings (%) |
| 🌶️ Heat Index | Feels-like temperature calculated and displayed |
| 🔄 State Sync | App always reflects the current physical LED state |
| 📊 Sensor History Chart | View temperature & humidity trends over time |
| 📱 Mobile Dashboard | Full control from iOS or Android via Blynk IoT app |

---

## 🛠️ Hardware Components

| Component | Quantity | Notes |
|-----------|----------|-------|
| ESP32 DevKit v1 | 1 | Microcontroller with built-in WiFi |
| DHT22 Sensor | 1 | Temperature & Humidity sensor |
| Red LED | 1 | Connected to GPIO 24 |
| Yellow LED | 1 | Connected to GPIO 27 |
| Green LED | 1 | Connected to GPIO 10 |
| Blue LED | 1 | Connected to GPIO 14 |
| 220Ω Resistors | 4 | Current limiting for each LED |
| Breadboard & Jumper Wires | — | For circuit assembly |

---

## 🔌 Circuit Diagram

```
ESP32              DHT22
GPIO 15  ────────  DATA
3.3V     ────────  VCC
GND      ────────  GND

ESP32              LEDs (via 220Ω resistors)
GPIO 24  ──[220Ω]──  Red    LED Anode → GND
GPIO 27  ──[220Ω]──  Yellow LED Anode → GND
GPIO 10  ──[220Ω]──  Green  LED Anode → GND
GPIO 14  ──[220Ω]──  Blue   LED Anode → GND
```

> 💡 **Tip:** You can visualize and run the full circuit for free on [Wokwi](https://wokwi.com/projects/443963082483615745) without any physical hardware.

---

## 📱 Blynk Virtual Pin Map

| Virtual Pin | Direction | Widget | Function |
|-------------|-----------|--------|----------|
| `V0` | Input | Button | Red LED toggle |
| `V1` | Input | Button | Yellow LED toggle |
| `V2` | Input | Button | Green LED toggle |
| `V3` | Input | Button | Blue LED toggle |
| `V4` | Output | Gauge/Chart | Temperature (°C) |
| `V5` | Output | Gauge/Chart | Humidity (%) |
| `V6` | Input | Button | Master (All LEDs) toggle |
| `V7` | Output | LED Indicator | Red LED status |
| `V8` | Output | LED Indicator | Yellow LED status |
| `V9` | Output | LED Indicator | Green LED status |
| `V10` | Output | LED Indicator | Blue LED status |
| `V11` | Output | Gauge | Heat Index (°C) |

---

## 🚀 Getting Started

### 1. Prerequisites

- [Arduino IDE](https://www.arduino.cc/en/software) with ESP32 board support
- [Blynk IoT App](https://blynk.io/) on your smartphone
- Libraries (install via Arduino Library Manager):
  - `Blynk` by Volodymyr Shymanskyy
  - `DHTesp` by beegee-tokyo

### 2. Clone the Repository

```bash
git clone https://github.com/YOUR_USERNAME/esp32-led-blynk.git
cd esp32-led-blynk
```

### 3. Set Up Blynk

1. Sign up at [blynk.cloud](https://blynk.cloud)
2. Create a new Template → set hardware to **ESP32**, connection to **WiFi**
3. Add Datastreams for V0–V11 (see [`docs/blynk-setup.md`](docs/blynk-setup.md) for the full table)
4. Create a Dashboard with buttons, gauges, and LED indicators
5. Add a new Device under the template → copy your **Auth Token**

> 📖 Full dashboard setup guide: [`docs/blynk-setup.md`](docs/blynk-setup.md)

### 4. Configure Credentials

Open `src/main.ino` and update these three lines:

```cpp
#define BLYNK_AUTH_TOKEN  "YOUR_AUTH_TOKEN_HERE"
char ssid[] = "YOUR_WIFI_SSID";
char pass[] = "YOUR_WIFI_PASSWORD";
```

> ⚠️ **Never commit real credentials to a public repo.** Use a private repo or environment variables.

### 5. Upload to ESP32

1. Connect ESP32 via USB
2. In Arduino IDE: **Tools → Board → ESP32 Dev Module**
3. Select the correct **COM port**
4. Click **Upload**
5. Open Serial Monitor at `115200` baud to verify connection

---

## 📂 Project Structure

```
esp32-led-blynk/
│
├── src/
│   ├── main.ino          # Main Arduino sketch
│   ├── diagram.json      # Wokwi circuit diagram
│   └── libraries.txt     # Required libraries list
│
├── docs/
│   └── blynk-setup.md    # Blynk dashboard configuration guide
│
├── .gitignore
└── README.md
```

---

## 🧠 How It Works

```
 ┌─────────────┐        WiFi / Cloud        ┌──────────────────┐
 │  Blynk App  │ ◄──────────────────────── │    Blynk Cloud   │
 │  (Mobile)   │ ──────────────────────────►│                  │
 └─────────────┘                            └────────┬─────────┘
                                                     │
                                                     │ WiFi
                                                     ▼
                                            ┌─────────────────┐
                                            │     ESP32       │
                                            │  ┌───────────┐  │
                                            │  │  DHT22    │  │
                                            │  │ Temp/Hum  │  │
                                            │  └───────────┘  │
                                            │  🔴 🟡 🟢 🔵    │
                                            │   LEDs x4       │
                                            └─────────────────┘
```

1. **User taps** a button in the Blynk app
2. Command travels to **Blynk Cloud** over the internet
3. ESP32 receives the command via **WiFi**
4. ESP32 sets the corresponding **GPIO pin** HIGH or LOW
5. LED turns **ON or OFF**
6. Meanwhile, the DHT22 sends **temperature & humidity** every 2 seconds back to the app

---

## 📊 Serial Monitor Output

```
==============================
  IoT LED Control + DHT22
==============================
[BLYNK] Connected to cloud!
[DHT22] Temp: 28.3°C | Humidity: 65.2% | Heat Index: 30.1°C
[DHT22] Temp: 28.4°C | Humidity: 65.0% | Heat Index: 30.2°C
[MASTER] All LEDs turned ON
[DHT22] Temp: 28.5°C | Humidity: 64.8% | Heat Index: 30.3°C
```

---

## 🔮 Future Improvements

- [ ] Add a buzzer alert when temperature exceeds a threshold
- [ ] OTA (Over-the-Air) firmware updates
- [ ] LED brightness control using PWM sliders
- [ ] RGB LED support with color picker in Blynk
- [ ] Local web dashboard (no cloud dependency)
- [ ] MQTT support as alternative to Blynk

---

## 🤝 Contributing

Pull requests are welcome! For major changes, please open an issue first to discuss what you'd like to change.

---

## 📄 License

This project is licensed under the [MIT License](LICENSE).

---

## 👤 Author

**Sumedha.C**
- GitHub: [@YOUR_USERNAME](https://github.com/YOUR_USERNAME)

---

<p align="center">
  Made with ❤️ using ESP32 & Blynk IoT
</p>

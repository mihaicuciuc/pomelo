# Pomelo - Complete Low-Power Gamma Ray Spectrometer

A complete low-power gamma ray spectrometer that can be used standalone or integrated into other projects.

![License](https://img.shields.io/badge/license-MIT-blue.svg)

## Overview

Pomelo is an open-source gamma ray spectroscopy system consisting of two main components:

- **[Pomelo Core](https://hackaday.io/project/194457-pomelo-gamma-spectroscopy-module)** - The gamma spectroscopy detection module
- **[Pomelo Zest](https://hackaday.io/project/196334-pomelo-hand-held-gamma-ray-spectrometer)** - A hand-held gamma ray spectrometer built around Pomelo Core

## Features

### Pomelo Core
- Low-power gamma ray detection and spectroscopy
- 1024-channel energy histogram
- Temperature-compensated high-voltage generation
- USB and UART interfaces for communication
- Configurable via stored parameters in EEPROM
- Coincidence detection support for multi-detector setups
- Real-time pulse output and dosimetry calculations
- Built on SAML21 microcontroller with custom bootloader (UF2 support)

### Pomelo Zest
- Portable hand-held spectrometer based on ESP32-C6
- 128x32 LCD display with backlight
- Three-button user interface
- Multiple display modes:
  - **CPM** - Counts per minute with history graph
  - **μSv/h** - Dose rate display
  - **Spectrum** - Real-time energy spectrum visualization
- Connectivity options:
  - **HTTP** - Built-in web server with live spectrum display
  - **BLE** - Bluetooth Low Energy data streaming
  - **SD Log** - Data logging to microSD card
  - **GPS Log** - Geo-tagged spectrum logging
- WiFi connectivity with mDNS support
- Deep sleep and light sleep power management
- Audio feedback (buzzer) for radiation pulses

## Repository Structure

```
pomelo-main/
├── Core/                          # Pomelo Core module
│   ├── v1_2/                      # Version 1.2
│   └── v1_3/                      # Version 1.3 (latest)
│       ├── bootloader/            # UF2 bootloader binaries
│       ├── firmware/              # Core firmware
│       │   └── PomeloCore/        # Atmel Studio project
│       │       ├── PomeloCore.uf2 # Pre-built firmware binary
│       │       └── PomeloCore/    # Source code
│       │           └── src/
│       │               ├── main.c         # Main firmware
│       │               └── nvm_params.c   # Parameter management
│       └── schematic/             # Hardware schematics (PDF)
│
├── Zest/                          # Pomelo Zest handheld device
│   ├── v1_2/                      # Version 1.2
│   └── v1_3/                      # Version 1.3 (latest)
│       ├── firmware/
│       │   ├── PomeloZest/        # Arduino project folder
│       │   │   ├── PomeloZest.ino # Main sketch
│       │   │   ├── app_*.ino      # Application modules
│       │   │   └── burn.bat       # Flashing script
│       │   └── httpFiles/         # Web interface files
│       │       ├── index.htm      # Main web interface
│       │       ├── uPlot.*        # Spectrum plotting library
│       │       └── *.png          # Favicon/icons
│       └── hardware/
│           ├── schematic/         # Hardware schematics (PDF)
│           ├── productionFiles/   # Manufacturing files
│           └── EasyEDA_Project.zip
│
├── Analysis/                      # Data analysis tools
│   └── gpsLogs/
│       ├── logsGroupFoliumPlots.py # GPS log visualization
│       └── foliumMapPlots.html    # Generated map visualization
│
├── LICENSE                        # MIT License
└── README.md                      # This file
```

## Getting Started

### Pomelo Core

#### Hardware Requirements
- SAML21 microcontroller-based board
- SiPM (Silicon Photomultiplier) detector
- Scintillator crystal

#### Building the Firmware
1. Open `Core/v1_3/firmware/PomeloCore/PomeloCore.atsln` in Atmel Studio / Microchip Studio
2. Build the project
3. Flash using the UF2 bootloader or a debugger

#### Pre-built Binary
A pre-built `PomeloCore.uf2` file is available in the firmware directory for easy flashing.

### Pomelo Zest

#### Hardware Requirements
- ESP32-C6 based board
- Pomelo Core module
- 128x32 ST7565 LCD display
- 3 buttons, buzzer, microSD slot (optional)
- GPS module (optional)

#### Building the Firmware
1. Install the Arduino IDE with ESP32 board support
2. Install required libraries:
   - `ArduinoJson`
   - `U8g2`
   - `EasyButton`
   - `ESP32Time`
   - `Adafruit GPS Library`
3. Open `Zest/v1_3/firmware/PomeloZest/PomeloZest.ino`
4. Select "ESP32C6 Dev Module" board
5. Compile and upload

#### Configuration
- WiFi credentials can be configured via the Settings menu or web interface
- Startup scripts can be stored for automatic configuration on boot

### Data Analysis

#### GPS Log Visualization
The `Analysis/gpsLogs/logsGroupFoliumPlots.py` script creates interactive maps from GPS-tagged radiation measurements:

```bash
cd Analysis/gpsLogs
python logsGroupFoliumPlots.py
```

Requirements:
- Python 3.x
- `numpy`, `matplotlib`, `folium`

This generates an interactive HTML map showing radiation levels at different locations with clickable spectra.

## Communication Protocol

### Core Commands (UART/USB)
| Command | Description |
|---------|-------------|
| `c`     | Request configuration parameters |
| `s`     | Request system status |
| `m`     | Request dosimetry data (CPM, μSv/h) |
| `h`     | Request spectrum histogram |

### Data Format
Responses are formatted as JSON for easy parsing:
- Dosimetry data includes CPM, dose rate, and measurement time
- Spectrum data includes 1024-channel histogram and calibration parameters
- System data includes temperature, serial number, and status flags

## Web Interface

When HTTP mode is enabled on Pomelo Zest, access the web interface at:
- `http://<device-ip>/` or
- `http://pomelo.local/` (if mDNS is enabled)

Features:
- Real-time spectrum display using uPlot
- Live dose rate and CPM readings
- Device configuration
- Time synchronization

## Contributing

Contributions are welcome! Please feel free to submit issues and pull requests.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

- Project created by [mihaicuciuc](https://github.com/mihaicuciuc)
- More details available on [Hackaday.io](https://hackaday.io/project/194457-pomelo-gamma-spectroscopy-module)

## Links

- [Pomelo Core on Hackaday.io](https://hackaday.io/project/194457-pomelo-gamma-spectroscopy-module)
- [Pomelo Zest on Hackaday.io](https://hackaday.io/project/196334-pomelo-hand-held-gamma-ray-spectrometer)

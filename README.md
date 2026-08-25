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

### Regular Commands

These are single-character commands that perform an action or retrieve information. They do **not** need to be followed by a newline (`\n`) or carriage return (`\r`).

* `h`: **Histogram**. Requests the device to send its current gamma-ray energy spectrum data. The output is a JSON string with details like counts per energy channel, temperature, and run time.
* `s`: **System Status**. Requests general information about the device's current state, including uptime, power status, and temperature. The output is a JSON string.
* `c`: **Configuration Dump**. Requests a detailed dump of all current configuration parameters, such as voltage settings, energy calibration, and output settings. The output is a JSON string.
* `x`: **Power On/Clear Spectrum**. Activates the main system power. If the detector is already running, this command can also be used to clear the current spectrum and start a fresh measurement.
* `z`: **Power Off**. Deactivates the main system power.
* `r`: **Load Parameters**. Instructs the device to reload all saved parameters from its non-volatile memory.
* `q`: **Print Parameters**. Prints all current parameters to the serial port in a formatted string. **Note**: This is a debugging command and may be removed in future versions.
* `g`: **CPM (Counts Per Minute)**. Requests the current counts per minute. The output is a float value.
* `u`: **uSv/h (micro-Sieverts per hour)**. Requests the current radiation dose rate. The output is a float value.
* `m`: **Measure Dosimetry**. Requests both the CPM and uSv/h values simultaneously. The output is a JSON string.
* `i`: **SiPM Current**. Requests the current draw of the SiPM sensor. The output is a JSON string.
* `p`: **Enter Parameter Mode**. This is a prefix command that prepares the device to receive a parameter-setting command in the `[parameter_ID]:[value]` format.
* `/`: **Boost SiPM power**. Activates boost mode for the SiPM high-voltage power supply.
* `*`: **Disable SiPM power boost**. Deactivates boost mode for the SiPM high-voltage power supply.

---

### Parameter Setting Commands

These commands allow you to set specific device parameters. They follow the format: `[parameter_ID]:[value]`.

| Serial Code | Name              | Description                                                                                                                              | Value Type/Range      |
| :--- | :--- | :--- | :--- |
| 0           | sipm\_vMin        | Sets the minimum operating voltage for the SiPM sensor.                                                                                  | Float, 0 to 4096      |
| 1           | sipm\_vMax        | Sets the maximum operating voltage for the SiPM sensor.                                                                                  | Float, 0 to 4096      |
| 2           | sipm\_v0deg       | Sets the bias voltage for the SiPM at 0°C. The actual voltage is extrapolated from this value based on temperature and `sipm_vTempComp`. | Float, 0 to 4096      |
| 3           | sipm\_vTempComp   | Temperature compensation coefficient for the SiPM bias voltage.                                                                            | Float, -5 to 5        |
| 4           | ecal\[0\]         | Energy calibration coefficient (offset). Used in the energy calculation: $E = ecal[0] + ch \cdot ecal[1] + ch^2 \cdot ecal[2]$                | Float                 |
| 5           | ecal\[1\]         | Energy calibration coefficient (linear).                                                                                                 | Float                 |
| 6           | ecal\[2\]         | Energy calibration coefficient (quadratic).                                                                                              | Float                 |
| 7           | uSvph\_constant   | Conversion constant for Sieverts per hour.                                                                                               | Float                 |
| 8           | vDac\[0\]         | First coefficient to obtain the DAC value for a requested voltage, as per: $dacValue = vDac[0] + vDac[1] \cdot requestedVolts$           | Float                 |
| 9           | vDac\[1\]         | Second coefficient for the voltage to DAC value conversion.                                                                              | Float                 |
| 10          | iMeas\[0\]        | Offset for current measurement.                                                                                                          | Float                 |
| 11          | iMeas\[1\]        | Slope for current measurement.                                                                                                           | Float                 |
| 12          | iMeas\[2\]        | Resistor value for current measurement.                                                                                                  | Float                 |
| 13          | threshold         | ADC threshold for pulse detection. This is a 12-bit value which corresponds to a channel cut of approximately `threshold / 4` in the output histogram. | Float, 1 to 4096      |
| 14          | sys\_outputs      | Configures the system outputs (e.g., enable/disable data streaming).                                                                     | Integer, 0 to 127     |
| 15          | sys\_coincidence  | Enables (1) or disables (0) coincidence mode.                                                                                            | Integer, 0 or 1       |
| 16          | sys\_pulseChar    | Sets the ASCII character for a fast UART pulse output.                                                                                   | Integer, 128 to 255   |

---

### Special Action Commands

These commands trigger specific functions and require a fixed numerical value as the parameter.

| Serial Code | Action                          | Required Value | Description                                          |
| :--- | :--- | :--- | :--- |
| 100         | Save parameters                 | -2024          | Saves all current parameters to non-volatile memory. |
| 200         | Start ADC calibration           | -2024          | Initiates the ADC calibration process.               |
| 300         | Initialize physics parameters   | -2024          | Resets the physics parameters to their default values. |
| 1000        | System reset (reboot)           | -2024          | Restarts the device.                                 |
| 2000        | Reset and enter bootloader mode | -2024          | Resets the device and enters the bootloader.         |

---

### Parameter Storage and Usage Notes

* **Parameter Storage**: The parameters are stored on different boards. **`ecal[]`** and **`sipm_v0deg`** are stored on the **Physics board** (the detector itself). All other parameters (`vDac[]`, `iMeas[]`, `threshold`, etc.) are stored on the **Core board**. This means if you swap detectors, the energy calibration and bias voltage settings will move with the detector. Recalibration is still recommended after swapping.
* **Unique Identification**: To uniquely identify each detector, use the **serial number** reported by the `h` and `s` commands. The `detString` parameter is not configurable.
* **Optimization**: You can optimize measurements by adjusting the **SiPM bias voltage** and **threshold** to cover the specific energy range of interest. For example, you can increase the SiPM voltage to shift the spectrum to a higher energy, but this may introduce noise at lower energies.
* **Procedure**: When you send a new parameter, it is applied immediately. It's recommended to wait a few seconds (especially for voltage changes) before using the `x` command to clear the spectrum and begin a new measurement. Once you are satisfied with the settings, use the **100:-2024** command to save them to non-volatile memory.
* **Safety Warning**: Be aware that the `sys_power` setting is saved to memory. If `sys_power` is `1` when you save, the detector will turn on immediately upon receiving power. If the device cannot read the `sipm_vMax` and `sipm_v0deg` parameters from the Physics board (e.g., if the board is uninitialized), the bias voltage could become dangerously high. To avoid this, always use the **`z`** command to turn off the detector before saving parameters. This ensures `sys_power` is saved as `0`, giving you a chance to configure the voltage parameters safely after the next power-on.


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

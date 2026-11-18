# ESP32-IDF Projects

A portfolio of embedded firmware projects built with
[Espressif ESP-IDF](https://idf.espressif.com/) and FreeRTOS for ESP32 devices.
This repository collects practical, documented applications as I develop my
skills in C, embedded systems, peripheral communication, and real-time firmware.

The projects range from hardware interaction to integrated applications. Each
folder is a standalone ESP-IDF project with its own source code and documentation,
making the repository easy to explore and extending it naturally with future work.

## Featured projects

| Project | Description |
| --- | --- |
| [CLI Lights](CLI_lights/) | Controls three LEDs through a menu-driven UART interface using GPIO and FreeRTOS tasks. |
| *More projects coming soon* | New completed applications will be added here as they are documented and public-ready. |

> **Portfolio note:** I keep completed projects here and leave local training
> exercises outside the repository. The featured section will grow as additional
> projects reach a documented, public-ready state.

## Skills demonstrated

- ESP-IDF project structure, CMake, components, and SDK configuration
- GPIO input and output for LEDs and buttons
- UART serial communication and menu-driven control
- FreeRTOS tasks, timing, scheduling, and queues
- I2C devices and environmental sensors
- HD44780 LCD integration
- Wi-Fi initialization and station-mode applications
- Modular firmware and inter-task message routing
- Hardware testing, debugging, flashing, and serial monitoring

## Repository layout

```text
ESP32-IDF/
├── CLI_lights/          # UART-controlled three-LED project
├── <future-project>/    # Additional completed ESP-IDF applications
└── README.md            # Repository introduction
```

Project folders are independent ESP-IDF applications. Each project documents
its purpose, hardware, build instructions, and important implementation details.
Pin assignments and hardware requirements may differ between projects.

## Building a project

Install and configure ESP-IDF, open a project folder, and use the standard
ESP-IDF workflow:

```bash
idf.py set-target esp32
idf.py build
idf.py -p PORT flash monitor
```

Replace `PORT` with the serial port assigned to your board. Check the project's
README for any additional hardware or configuration requirements.

## Project status

This is an actively growing portfolio. Projects are presented as working
learning applications unless explicitly described otherwise. Completed projects
may continue to evolve as the implementation improves or supporting hardware
changes.

## License

No repository-wide license has been selected yet. Individual projects should
not be assumed to have a license until one is added.

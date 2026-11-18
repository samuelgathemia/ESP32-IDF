# CLI Lights

An ESP-IDF learning project that controls three LEDs from a serial command-line
interface. Each LED can be turned on, turned off, or made to blink.

The project is intentionally small and demonstrates:

- UART initialization and serial input handling.
- GPIO output configuration.
- FreeRTOS tasks for independent LED control.
- A simple two-level command prompt.
- Shared state between a UART command task and LED tasks.

## Features

On startup, all three LEDs are off. The firmware listens for commands on UART0:

1. Select an LED.
2. Select an action for that LED:
   - `1` - turn it on
   - `2` - turn it off
   - `3` - blink it

Blinking uses a 500 ms on / 500 ms off interval. The selected mode remains
active until another action is chosen for that LED.

## Hardware

The firmware assumes three external LEDs connected as follows:

| LED | ESP32 GPIO | Suggested connection |
| --- | ---: | --- |
| LED 1 | GPIO 2 | GPIO 2 → resistor → LED anode; LED cathode → GND |
| LED 2 | GPIO 4 | GPIO 4 → resistor → LED anode; LED cathode → GND |
| LED 3 | GPIO 16 | GPIO 16 → resistor → LED anode; LED cathode → GND |

Use an appropriate current-limiting resistor for each LED, typically 220 Ω to
1 kΩ. The firmware assumes the LEDs are active-high: a GPIO level of `1` turns
an LED on.

### UART connection

The application uses UART0 with the default ESP32 serial pins:

| Signal | GPIO |
| --- | ---: |
| TX | GPIO 1 |
| RX | GPIO 3 |

UART settings:

- Baud rate: `115200`
- Data bits: `8`
- Parity: none
- Stop bits: `1`
- Flow control: disabled

On development boards with a USB-to-UART bridge, the board's USB connection
usually provides this serial interface. If using an external USB-to-UART
adapter, connect TX to RX, RX to TX, and share GND. Use 3.3 V logic levels.

> **Note:** GPIO 2 is a bootstrapping pin on many ESP32 boards. If the board
> does not boot reliably with the LED circuit attached, disconnect the circuit
> while flashing or choose another output pin in `main/main.c`.

## Serial interaction

After opening the serial monitor, enter an LED number:

```text
1
```

The firmware then displays:

```text
Choose led task (1 - 3):
 1. on
 2. off
 3. blink
```

Enter the action number. For example, selecting LED 2 and making it blink:

```text
2
Choose led task (1 - 3):
 1. on
 2. off
 3. blink
3
led blinking
```

Any other first-level input prints `Unknown command`. Any other action input
prints `Invalid function` and keeps the action prompt open.

## Project structure

```text
CLI_lights/
├── CMakeLists.txt       # ESP-IDF project definition
├── README.md            # Project documentation
└── main/
    ├── CMakeLists.txt   # Main component registration
    └── main.c           # UART, command handling, and LED tasks
```

The application creates four FreeRTOS tasks:

- `uart_task` reads serial input and selects an LED.
- `led1_task` drives LED 1.
- `led2_task` drives LED 2.
- `led3_task` drives LED 3.

Each LED task reads its LED's current mode and updates the corresponding GPIO.

## Requirements

- An ESP32 development board.
- ESP-IDF installed and configured.
- A serial terminal or the ESP-IDF monitor.
- Three LEDs and current-limiting resistors.

This project uses the ESP-IDF APIs included with the framework and does not
declare any additional managed components.

## Build and run

Open a terminal with the ESP-IDF environment enabled, then change into this
project directory:

```bash
cd CLI_lights
```

Set the target if necessary:

```bash
idf.py set-target esp32
```

Build the firmware:

```bash
idf.py build
```

Replace `/dev/ttyUSB0` with the serial port for your board, then flash and
start the monitor:

```bash
idf.py -p /dev/ttyUSB0 flash monitor
```

To leave the monitor, press `Ctrl-]`.

## Learning notes and limitations

This is a learning project rather than a production-ready CLI. In particular:

- The command interface is numeric and menu-driven; it is not an
  `esp_console` command registry.
- UART input and LED mode state are shared between tasks without a mutex.
  This is adequate for the simple interaction pattern but should be revisited
  as the application grows.
- UART and GPIO initialization return values are not currently checked.
- UART0 is also commonly used for boot logs and flashing, so unrelated serial
  output may appear in the terminal.
- The GPIO assignments are hard-coded in `main/main.c` and should be adjusted
  for a different board or wiring layout.

## License

No license file is currently included. Add a license before redistributing this
project publicly.

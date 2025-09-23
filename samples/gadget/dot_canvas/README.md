# dot_canvas

Pixel art sketches.

Both sample projects (`dot_canvas_simple` and `dot_canvas_advanced`) are designed for the Seeed Studio XIAO 6x10 RGB Matrix.

Hardware reference: [Seeed Studio RGB Matrix for XIAO](https://wiki.seeedstudio.com/rgb_matrix_for_xiao/)

This sketch uses [Adafruit_NeoPixel](https://github.com/adafruit/Adafruit_NeoPixel/tree/master).

---

## Getting Started

### 1. Install `arduino-cli`

Make sure you have `arduino-cli` installed.  
Tested with:
arduino-cli Version: 1.3.1 Commit: 08ff7e2b Date: 2025-08-28T13:51:45Z

### 2. Initialize and Configure

Generate a default configuration file:

```bash
arduino-cli config init
```

Edit the generated arduino-cli.yaml and add the 3rd-party package URL for XIAO RP2040/RP2350:

```yaml
board_manager:
    additional_urls:
        - https://github.com/earlephilhower/arduino-pico/releases/download/global/package_rp2040_index.json
```

Verify the URL was registered correctly:

```bash
arduino-cli config dump
```

Expected output (excerpt):

```bash
board_manager:
    additional_urls:
        - https://github.com/earlephilhower/arduino-pico/releases/download/global/package_rp2040_index.json

```

### 3. Update Core Index

```bash
arduino-cli core update-index
```

You should see:

```bash
Downloading index: package_index.tar.bz2 downloaded
Downloading index: package_rp2040_index.json downloaded
```

### 4. Search and Install RP2040 Core

Search for available cores:

```bash
arduino-cli core search rp2040
```

Expected output (excerpt):

```bash
ID                  Version Name
arduino:mbed_nano   4.4.1   Arduino Mbed OS Nano Boards
arduino:mbed_rp2040 4.4.1   Arduino Mbed OS RP2040 Boards
rp2040:rp2040       5.1.0   Raspberry Pi Pico/RP2040/RP2350
arduino:mbed        3.3.0   [DEPRECATED] Arduino Mbed OS Boards
```

Install the RP2040 core:

```bash
arduino-cli core install rp2040:rp2040
```
Verify installation:

```bash
arduino-cli core list
```
Expected output (excerpt):

```bash
$ arduino-cli core list
ID            Installed Latest Name
rp2040:rp2040 5.1.0   5.1.0  Raspberry Pi Pico/RP2040/RP2350

```

### 5. Build and Upload

Example for XIAO RP2040.
Make sure to adjust the serial port number (`-p /dev/ttyACM0`) in `upload.sh` as needed for your system.

```bash
cd ./dot_canvas_simple
./build.sh
```
Put the board into BOOTSEL mode (press and hold the BOOT button while connecting the USB cable),
then run:

```bash
./upload.sh
```

For RP2350, modify the compile.profile section in `mgc-sketch.yaml` as follows:

```yaml
 compile:
   verbose: true
 #  profile: xiao_rp2040
   profile: xiao_rp2350 
```

Also update `upload.sh`:

```bash
#!/bin/bash

#arduino-cli upload --profile xiao_rp2040 -p /dev/ttyACM0 --input-file ./build/dot_canvas_simple.ino.uf2
arduino-cli upload --profile xiao_rp2350 -p /dev/ttyACM0 --input-file ./build/dot_canvas_simple.ino.uf2
```

## Demo Video

The following video shows a demo using the `dot_canvas_advanced` sketch:

https://youtube.com/shorts/6klF4XKFNUo


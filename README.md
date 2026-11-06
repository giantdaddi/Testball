# Trackball test firmware

Minimal ZMK firmware to check that one PMW3610 sensor tracks the ball.
Hardware: nice!nano v2, one PMW3610 module, breadboard.

## Wiring

| Sensor module | nice!nano |
|---|---|
| VDD, VDDIO, NRESET | VCC (3.3 V), never RAW or B+ |
| GND | GND |
| SCLK | P0.17 |
| SDIO | P0.20 |
| NCS | P1.00 |
| MOTION | P0.11 |

Optional buttons (each between the pin and GND):
- P1.04: left click
- P1.06: clear Bluetooth pairing

## Build

1. Create a new GitHub repository and upload all these files, keeping the folders.
2. Open the **Actions** tab. A build starts automatically (or press "Run workflow").
3. When it finishes (green tick, ~5 min), download the **firmware** artifact and unzip it.

## Flash

1. Plug the nice!nano into your computer with USB-C.
2. Double-tap reset (or short RST to GND twice quickly). A drive called `NICENANO` appears.
3. Drag `trackball_test-nice_nano-zmk.uf2` onto it. It reboots by itself.

## Test

- **USB:** the cursor should move as soon as it's plugged in.
- **Bluetooth:** pair with "Trackball Test" in your computer's Bluetooth settings.
- Hold the ball about 2.4 mm above the lens and roll it.

## If something's off

| Problem | Fix |
|---|---|
| Cursor moves the wrong way | Uncomment `invert-x;`, `invert-y;` or `swap-xy;` in the overlay |
| Too slow / too fast | Change `cpi = <800>;` (e.g. 400-1600) |
| Nothing moves | Check wiring and lens height; enable the logging lines in the `.conf` |
| Pairing stuck | Flash the `settings_reset` file, then the trackball file again |

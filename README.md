# Machine Temperature Monitor

Reads a JSON file of machines, checks each one's temperature, and turns power off automatically if it's overheating. Then saves the result back to the file.

## Goal

Simulate a basic safety system: any machine above 90°C gets shut off (`power: false`), everything else stays on. Written in C using the [cJSON](https://github.com/DaveGamble/cJSON) library.

## How it works

Reads `report.json` into memory
Parses it with cJSON
Loops through each machine and checks `temp`
Updates `power` based on the temperature
Writes the updated JSON back to `report.json`

## Example

| ID | Name | Temp (°C) | Before | After |
|----|------|-----------|--------|-------|
| 1 | Hammer | 91.4 | true | false |
| 2 | Drill Press | 82.1 | false | true |
| 3 | Lathe | 93.7 | true | false |
| 4 | CNC Mill | 78.5 | false | true |
| 5 | Hydraulic Press | 92.2 | true | false |
| 6 | Band Saw | 65.8 | false | true |
| 7 | Laser Cutter | 91.0 | true | false |
| 8 | Grinder | 88.3 | false | true |
| 9 | Plasma Torch | 93.6 | true | false |
| 10 | Waterjet Cutter | 52.4 | false | true |

## Run it

```bash
gcc main.c cJSON/cJSON.c -o monitor.exe && monitor.exe
```

Make sure `report.json` is in the same folder.

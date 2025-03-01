# phoenix-fc
Phoenix Flight Computer/Controller

# Main functions

## Launch Sequence
Launch sequence has four stages \
Each stage is coded by a six digit binary representation: from left to right: \
First two digits represent the release valve
* 00: default state, valve close
* 01: release valve open, venting pressure
* 10: arm valve open

Second two digits represent the fuel valve 1
* 00: default state, valve close
* 01: release valve open, venting pressure
* 10: fuel valve 1 valve open

Third two digits represent the fuel valve 2
* 00: default state, valve close
* 01: release valve open, venting pressure
* 10: fuel valve 2 valve open

### PRE-ARM
* default state, nothing happens
* all valves closed

### ARMED: system prepared, waiting to open fuel valves
* arm valve open

### ABORT: emergency break, close all fuel valves
* release valves for arm, fuel valve 1, fule valve 2 open
* emergency break

### LAUNCH: two main fuel values are opened, rocket 
* after arm valve is opend
* two fuel valves open for mixing
* rocket launching, no way back


### Buttons/Swithces
* Abort (button): has highest priority, open release valve for all
* Arm (switch): open/close arm valves
* Launch (button): open two fuel valves


![My Image](./lib/diagrams/pheonix-fc-launch-control-auto.svg)

# phoenix-fc
Phoenix Flight Computer/Controller

# Main functions

## Launch Sequence (Auto Mode)
Launch sequence has four stages \
Each stage is coded by a six digit binary representation \
Each two digits representation:
* 00: flow valve close, vent valve close
* 10: flow valve open, vent valve close
* 10: flow valve close, vent valve open
* 11: forbiden state, cannot open flow and vent at the same time

From left to right, each two digits represents the state for: \
(arm | fuel valve 1 | fuel valve2 ) \
Each state has two valves: flow valve and vent valve

### PRE-ARM (00|00|00)
* default state, nothing happens
* all valves closed

### ARMED (10|00|00)
* arm flow valve open

### ABORT (01|01|01)
* open vent valves for all 
* emergency break, abort the mission

### LAUNCH:(10|10|10)
* after arm flow valve is opend
* open the flow valevs for both fuels
* rocket launching, no way back


### Buttons/Swithces
* Abort (button): has highest priority, open vent valves for all
* Arm (switch): open/close arm flow valve
* Launch (button): open fuel 1&2 flow valves

![My Image](./lib/diagrams/pheonix-fc-launch-control-auto.svg)

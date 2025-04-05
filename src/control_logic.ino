//Using binary literal for rocket state
#include <system_error>
const uint8_t PRE_ARM = 0b000000;  //0  decimal
const uint8_t ABORT   = 0b010101;  //21 decimal
const uint8_t ARMED   = 0b100000;  //32 decimal
const uint8_t LAUNCH  = 0b101010;  //42 decimal

//Current state of the rocket
uint8_t rocketState = PRE_ARM;

//Possible inputs
enum ButtonPress {
  NONE,
  ABORT_BTN,
  ARM_BTN,
  LAUNCH_BTN
};

ButtonPress getButtonPress() {
  //TODO: Replace with real pin reading logic or test code
  //only one button press should be registered at one time
  //if multiple button reads are registered, must have set priority.
  return NONE;
}

void setValves() {
  //TODO: set valves open/closed based on state
  bool gn2_flow = rocketState & 0b100000;
  bool gn2_vent = rocketState & 0b010000;
  bool lng_flow = rocketState & 0b001000;
  bool lng_vent = rocketState & 0b000100;
  bool lox_flow = rocketState & 0b000010;
  bool lox_vent = rocketState & 0b000001;
}

void setup() {
  //TODO: Implement actual setup 
  //Arm: gn2
  //Fuel1: lng
  //Fuel2: lox

  rocketState = PRE_ARM; //start in PRE_ARM
}

void loop() {
  // put your main code here, to run repeatedly:
  ButtonPress press = getButtonPress();

  //State machine for rocket
  switch (rocketState) {

    case PRE_ARM:
      if (press == ABORT_BTN) {
        rocketState = ABORT;
      }
      else if (press == ARM_BTN) {
        rocketState = ARMED;
      }
      //else remain in PRE_ARM
      break;

    case ARMED:
      if (press == ABORT_BTN) {
        rocketState = ABORT;
      }
      else if (press == LAUNCH_BTN) {
        rocketState = LAUNCH;
      }
      else if (press == ARM_BTN) {
        //might have to modify depending on how switch is read
        rocketState = PRE_ARM;
      }
      break;

    case LAUNCH:
      //rocket is launching, possibly try to abort?
      if (press == ABORT_BTN) {
        rocketState = ABORT;
      }
      break;

    case ABORT:
      //if in abort cannot get out
      break;
  }

  //TODO: based on current state modify valves
  setValves(rocketState); //TODO: implement
  delay(50); // small debounce or loop delay
}

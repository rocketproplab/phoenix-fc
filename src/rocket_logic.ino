//Rocket States
const uint8_t PRE_ARM = 0b000000;  // All valves closed
const uint8_t ARMED   = 0b100000;  // Only arm flow valve open
const uint8_t ABORT   = 0b010101;  // All vent valves open, flow valves closed
const uint8_t LAUNCH  = 0b101010;  // All flow valves open, vent valves closed

// Subsystem Values
const uint8_t SUBSYSTEM_ARM = 0;
const uint8_t SUBSYSTEM_FUEL_1 = 1;
const uint8_t SUBSYSTEM_FUEL_2 = 2;
const char* subsystemNames[] = {"Arm", "Fuel1", "Fuel2"};

//Global Variables to Track Current Valve States
//false = CLOSED, true = OPEN
bool currentArmFlow   = false;
bool currentArmVent   = false;
bool currentFuel1Flow = false;
bool currentFuel1Vent = false;
bool currentFuel2Flow = false;
bool currentFuel2Vent = false;


void setup() {
  //TODO: implement setup and initalize pins, etc
}

void loop() {
  //receive the rocket state from ground arduino
  uint8_t rocketState = receiveRocketState();

  //move the valves/vents based on the received state
  updateRocketValves(rocketState);

  //optionally can add delay here to simulate processing
}

//dummy function to receive the rocket state
uint8_t receiveRocketState() {
  //TODO: implement the actual reading from serial
  //determine if we want to check validity of transmitted data
  static uint8_t currentState = PRE_ARM;
  if (Serial.available() > 0) {
    char ch = Serial.read();
    switch (ch) {
      case 'p': currentState = PRE_ARM; break;
      case 'a': currentState = ARMED;   break;
      case 'b': currentState = ABORT;   break;
      case 'l': currentState = LAUNCH;  break;
      default: break; //TODO: add ability to handle errors better (ie corrupted data)
    }
  }
  return currentState;
}

//update rocket valves based on received state
void updateRocketValves(uint8_t state) {
  //decode each pair of bits 00|00|00
  //bits 5-4: arm pair; bits 3-2: fuel valve 1 pair; bits 1-0: fuel valve 2 pair
  uint8_t armBitPair   = (state >> 4) & 0x03;  //top 2 bits
  uint8_t fuel1BitPair = (state >> 2) & 0x03;  //middle 2 bits
  uint8_t fuel2BitPair = state & 0x03;         //bottom 2 bits

  Serial.println("----------");
  Serial.print("Received Rocket State: ");
  Serial.println(state, BIN); //print state in binary

  //update each subsystem based on its 2-bit state
  //TODO: determine if order of opening/closing matters
  applyValveState(SUBSYSTEM_ARM, armBitPair);
  applyValveState(SUBSYSTEM_FUEL_1, fuel1BitPair);
  applyValveState(SUBSYSTEM_FUEL_2, fuel2BitPair);
}

//helper function to map a 2-bit pair to valve/vent opening/closing
void applyValveState(const uint8_t subsystem, uint8_t pair) {
  //print info on which values are being modified
  Serial.print(subsystemNames[subsystem]);
  Serial.print(" state (2-bit): ");
  Serial.println(pair, BIN); //print bit pair in binary

  switch(pair) {
    case 0b00:
      //both flow and vent remain closed
      closeFlow(subsystem);
      closeVent(subsystem);
      break;
    case 0b10:
      //open flow valve; keep vent closed
      openFlow(subsystem);
      closeVent(subsystem);
      break;
    case 0b01:
      //open vent valve; keep flow closed
      closeFlow(subsystem);
      openVent(subsystem);
      break;
    default:
      //forbidden state (11) encountered
      Serial.print("Error: Forbidden state for ");
      Serial.println(subsystemNames[subsystem]);
      break;
  }
}

//valve/vent command functions with state tracking
//ensures if a vent/valve is already open/closed we don't try to open/close it again

void openFlow(const uint8_t subsystem) {
  if (subsystem == SUBSYSTEM_ARM) {
    if (!currentArmFlow) {
      Serial.println("Arm flow: OPENING");
      // TODO: (code to physically open the valve goes here.)
      currentArmFlow = true;
    } else {
      Serial.println("Arm flow is already OPEN");
    }
  }
  else if (subsystem == SUBSYSTEM_FUEL_1) {
    if (!currentFuel1Flow) {
      Serial.println("Fuel1 flow: OPENING");
      // TODO: (code to physically open the valve goes here.)
      currentFuel1Flow = true;
    } else {
      Serial.println("Fuel1 flow is already OPEN");
    }
  }
  else if (subsystem == SUBSYSTEM_FUEL_2) {
    if (!currentFuel2Flow) {
      Serial.println("Fuel2 flow: OPENING");
      // TODO: (code to physically open the valve goes here.)
      currentFuel2Flow = true;
    } else {
      Serial.println("Fuel2 flow is already OPEN");
    }
  }
}

void closeFlow(const uint8_t subsystem) {
  if (subsystem == SUBSYSTEM_ARM) {
    if (currentArmFlow) {
      Serial.println("Arm flow: CLOSING");
      // TODO: (code to physically close the valve goes here.)
      currentArmFlow = false;
    } else {
      Serial.println("Arm flow is already CLOSED");
    }
  }
  else if (subsystem == SUBSYSTEM_FUEL_1) {
    if (currentFuel1Flow) {
      Serial.println("Fuel1 flow: CLOSING");
      // TODO: (code to physically close the valve goes here.)
      currentFuel1Flow = false;
    } else {
      Serial.println("Fuel1 flow is already CLOSED");
    }
  }
  else if (subsystem == SUBSYSTEM_FUEL_2) {
    if (currentFuel2Flow) {
      Serial.println("Fuel2 flow: CLOSING");
      // TODO: (code to physically close the valve goes here.)
      currentFuel2Flow = false;
    } else {
      Serial.println("Fuel2 flow is already CLOSED");
    }
  }
}

void openVent(const uint8_t subsystem) {
  if (subsystem == SUBSYSTEM_ARM) {
    if (!currentArmVent) {
      Serial.println("Arm vent: OPENING");
      // TODO: (code to physically open the vent goes here.)
      currentArmVent = true;
    } else {
      Serial.println("Arm vent is already OPEN");
    }
  }
  else if (subsystem == SUBSYSTEM_FUEL_1) {
    if (!currentFuel1Vent) {
      Serial.println("Fuel1 vent: OPENING");
      // TODO: (code to physically open the vent goes here.)
      currentFuel1Vent = true;
    } else {
      Serial.println("Fuel1 vent is already OPEN");
    }
  }
  else if (subsystem == SUBSYSTEM_FUEL_2) {
    if (!currentFuel2Vent) {
      Serial.println("Fuel2 vent: OPENING");
      // TODO: (code to physically open the vent goes here.)
      currentFuel2Vent = true;
    } else {
      Serial.println("Fuel2 vent is already OPEN");
    }
  }
}

void closeVent(const uint8_t subsystem) {
  if (subsystem == SUBSYSTEM_ARM) {
    if (currentArmVent) {
      Serial.println("Arm vent: CLOSING");
      // TODO: (code to physically close the vent goes here.)
      currentArmVent = false;
    } else {
      Serial.println("Arm vent is already CLOSED");
    }
  }
  else if (subsystem == SUBSYSTEM_FUEL_1) {
    if (currentFuel1Vent) {
      Serial.println("Fuel1 vent: CLOSING");
      // TODO: (code to physically close the vent goes here.)
      currentFuel1Vent = false;
    } else {
      Serial.println("Fuel1 vent is already CLOSED");
    }
  }
  else if (subsystem == SUBSYSTEM_FUEL_2) {
    if (currentFuel2Vent) {
      Serial.println("Fuel2 vent: CLOSING");
      // TODO: (code to physically close the vent goes here.)
      currentFuel2Vent = false;
    } else {
      Serial.println("Fuel2 vent is already CLOSED");
    }
  }
}
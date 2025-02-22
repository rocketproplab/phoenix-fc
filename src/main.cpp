#include <Arduino.h>

enum State {
    PRE_ARM,
    ABORT,
    ARMED,
    LAUNCH
};

State currentState = PRE_ARM; // Initial state


void setup() {
    // Setup code is run once at the beginning
    Serial.begin(9600);
}

void loop() {
    // Main loop code is run repeatedly, like a while loop
    switch (currentState) {
        case PRE_ARM:
            // Pre-arm state code
            // Emit off for all valves
            break;
        case ABORT:
            // Abort state code
            // Disable all flow valves, enable all vent valves
            break;
        case ARMED:
            // Armed state code
            // Enable the pilot flow valve
            break;
        case LAUNCH:
            // Launch state code
            // Enable the fuel flow and oxidizer flow valve
            break;
    }
}


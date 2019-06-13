/*
 * Daniel Song
 * February 23, 2019
 * 4-bit binary counter+display that optionally uses a switch to step the counter
 */

// number of bits to display
const int BITS = 4;
// number of binary numbers to display per second
const int NUMS_PER_SECOND = 4;
// whether to use the switch or not
const bool USE_SWITCH = false;

// array of pins to display the number on
const int pins[BITS] = { 10, 8, 7, 5 };
// pin that the switch is connected to
const int switchPin = 12;

// current number to display
int num = 0;
// stores the last state of the switch, used to detect transitions from LOW to HIGH
bool lastSwitchState = LOW;
bool curSwitchState = LOW;

void setup() {
  // setup all LED pins as output
  for (int i = 0; i < BITS; i++)
    pinMode(pins[i], OUTPUT);
}

// helper function that displays the number on the binary display
void displayBinary(int numToDisplay) {
  // gets bit i from numToDisplay and displays it on the corresponding LED (pins[i])
  for (int i = 0; i < BITS; i++)
    digitalWrite(pins[i], bitRead(numToDisplay, i));
}

void loop() {
  // display the number
  displayBinary(num);

  // uses the switch to increase the number instead of automatically increasing
  if (USE_SWITCH) {
    // read switch state
    curSwitchState = digitalRead(switchPin);

    // only increment if the switch goes from LOW to HIGH
    if (curSwitchState == HIGH && lastSwitchState == LOW) {
      // increment the number
      num++;

      // brief delay to prevent bouncing of the switch
      delay(10);
    }

    // update last switch state
    lastSwitchState = curSwitchState;
  } else {
    // automatically increase the number to display
    num++;

    // delay to make the numbers display at the desired NUMS_PER_SECOND
    delay(1000 / NUMS_PER_SECOND);
  }
}

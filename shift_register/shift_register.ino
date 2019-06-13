// I/O pin for shift register clock
int clockPin = 4;
// I/O pin for shift register data input
int dataPin = 19;

// setup output pins
void setup() {
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

// binary representations of the numbers 0 to 9 on a 7-segment display (ABGFEDCP order)
int digits[10] = { B11011110, B01000010, B11101100, B11100110, B01110010, B10110110, B10111110, B11000010, B11111110, B11110110 };

void loop() {
  // output the binary representations of the numbers 0 to 9 to the shift register
  for (int i = 0; i < 10; i++) {
    shiftOut(dataPin, clockPin, LSBFIRST, digits[i]);
    delay(250);
  }
}

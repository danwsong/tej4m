/*
 * Daniel Song
 * February 28, 2019
 * 30-frame animation on an 8x8 LED matrix
 */

// number of frames in the animation
const int NUM_FRAMES = 30;
// number of frames to display per second
const int FRAMES_PER_SECOND = 30;
// number of times the image must be scanned through for one second to pass, DO NOT CHANGE
const int SCANS_PER_SECOND = 1200;

// array that maps pins on the LED grid to pins on the Arduino
const int pinMap[16] = { 11, 10, 14, 15, 16, 17, 18, 19, 2, 3, 4, 5, 6, 7, 8, 9 };
// array that maps rows on the LED grid to the cathode pins
const int cathodes[8] = { 8, 13, 7, 11, 0, 6, 1, 4 };
// array that maps columns on the LED grid to the anode pins
const int anodes[8] = { 12, 2, 3, 9, 5, 10, 14, 15 };

// 30-frame animation to be displayed
// each row of each frame is stored as an 8-bit binary number
// for each bit, a 1 turns on the corresponding LED, while a 0 turns it off
// for example, a B01100111 codes for a row like this:
// OFF ON ON OFF OFF ON ON ON
const byte animation[NUM_FRAMES][8] = {
  {
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
  },
  {
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
  },
  {
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
  },
  {
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
  },
  {
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
  },
  {
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B10000000,
  },
  {
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B10000000,
    B11000000,
  },
  {
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B11000000,
    B11100000,
    B11100000,
  },
  {
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B11000000,
    B11100000,
    B11110000,
    B11110000,
  },
  {
    B00000000,
    B00000000,
    B00000000,
    B11000000,
    B11110000,
    B11110000,
    B11111000,
    B11111000,
  },
  {
    B00000000,
    B00000000,
    B11000000,
    B11110000,
    B11111000,
    B11111000,
    B11111100,
    B11111100,
  },
  {
    B00000000,
    B11100000,
    B11110000,
    B11111000,
    B11111100,
    B11111110,
    B11111110,
    B11111110,
  },
  {
    B11100000,
    B11111000,
    B11111100,
    B11111110,
    B11111110,
    B11111111,
    B11111111,
    B11111111,
  },
  {
    B11111000,
    B11111100,
    B11111110,
    B11111111,
    B11111111,
    B11111111,
    B11111111,
    B11111111,
  },
  {
    B11111110,
    B11111111,
    B11111111,
    B11111111,
    B11111111,
    B11111111,
    B11111111,
    B11111111,
  },
  {
    B11111111,
    B11111111,
    B11111111,
    B11111111,
    B11111111,
    B11111111,
    B11111111,
    B11111111,
  },
  {
    B11111111,
    B11111111,
    B11111111,
    B11111111,
    B11111111,
    B11111111,
    B11111111,
    B11111111,
  },
  {
    B11111111,
    B11111111,
    B11111111,
    B11111111,
    B11111111,
    B11111111,
    B11111111,
    B11111111,
  },
  {
    B11111111,
    B11111111,
    B11111111,
    B11111111,
    B11111111,
    B11111111,
    B11111111,
    B11111111,
  },
  {
    B11111111,
    B11111111,
    B11111111,
    B11111111,
    B11111111,
    B11111111,
    B11111111,
    B11111111,
  },
  {
    B11111110,
    B11111111,
    B11111111,
    B11111111,
    B11111111,
    B11111111,
    B11111111,
    B11111111,
  },
  {
    B11111100,
    B11111110,
    B11111111,
    B11111111,
    B11111111,
    B11111111,
    B11111111,
    B11111111,
  },
  {
    B11111000,
    B11111000,
    B11111100,
    B11111111,
    B11111111,
    B11111111,
    B11111111,
    B11111111,
  },
  {
    B11110000,
    B11110000,
    B11111000,
    B11111100,
    B11111111,
    B11111111,
    B11111111,
    B11111111,
  },
  {
    B11100000,
    B11100000,
    B11110000,
    B11110000,
    B11111100,
    B11111111,
    B11111111,
    B11111111,
  },
  {
    B11000000,
    B11000000,
    B11100000,
    B11100000,
    B11110000,
    B11111100,
    B11111111,
    B11111111,
  },
  {
    B10000000,
    B10000000,
    B10000000,
    B11000000,
    B11100000,
    B11110000,
    B11111000,
    B11111111,
  },
  {
    B00000000,
    B00000000,
    B00000000,
    B10000000,
    B10000000,
    B11000000,
    B11100000,
    B11111000,
  },
  {
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B10000000,
    B11000000,
    B11100000,
  },
  {
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B10000000,
  },
};
// stores which frame the animation is on
int curFrame = 0;

void setup() {
  // setup all LED pins as output
  for (int i = 0; i < 16; i++)
    pinMode(pinMap[i], OUTPUT);
}

// helper function that displays the current frame of the animation
void displayFrame(int frameToDisplay) {
  // SCANS_PER_SECOND / FRAMES_PER_SECOND = SCANS_PER_FRAME is the number of times to loop each frame
  // so that the animation is played backed at the desired FRAMES_PER_SECOND
  for (int i = 0; i < SCANS_PER_SECOND / FRAMES_PER_SECOND; i++) {
    for (int r = 0; r < 8; r++) {
      // turn on cathode for row r
      digitalWrite(pinMap[cathodes[r]], LOW);
      // turn on the LEDs in the row that should be turned on for the given frame and row
      for (int c = 0; c < 8; c++)
        // output the bit at the current frame, row, and column on the corresponding LED
        digitalWrite(pinMap[anodes[c]], bitRead(animation[frameToDisplay][r], c));
      // turn off all LEDs in the row
      for (int c = 0; c < 8; c++)
        digitalWrite(pinMap[anodes[c]], LOW);
      // turn off cathode for row r
      digitalWrite(pinMap[cathodes[r]], HIGH);
    }
  }
}

void loop() {
  // display the frame
  displayFrame(curFrame);
  // go to the next frame
  curFrame++;
  // go back to the start of the animation if the end is reached
  if (curFrame == NUM_FRAMES)
    curFrame = 0;
}

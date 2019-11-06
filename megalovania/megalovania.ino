/* Button and leds which interacts with the melody "megalovania"
 * 
 * When the button is pressed, the melody will play and the leds will interact with the different tones. 
 * It depends on the note which colour lights up. 
 * 
 * Following leds will light up when:
 *  - the tone D is played --> green
 *  - the tone G or Ges is played --> yellow
 *  - the tone F is played --> red
 *  - the tone A or C is played --> white
 * 
 * The oter white led will be blinking constantly, while the button is not pressed.
 * 
 * Little tip: Hold the button for a longer time pressed.
 * 
 * The constellation:
 *  - button attached to pin 12 from 10K resistor from ground
 *  - button attached to middle buzzer pin from 5.0V
 *  - buzzer attached to pin 8 from ground
 *  - led attached to resistor to pin 6 from ground
 *  - green led attached to resistor to pin 5 from ground
 *  - yellow attached to resistor to pin 4 from ground
 *  - red attached to resistor to pin 3 from ground
 *  - white attached to resistor to pin 2 from ground
 * 
 * @author Mia Gudelj, Clarissa Sulivan
 * @since 03.11.2019
 * @version 1.0
 */
 
 #include "pitches.h"

// ---LED---
int ledPin = 6;
int ledPinGreen = 5;
int ledPinYellow = 4;
int ledPinRed = 3;
int ledPinWhite = 2;

// --- BUTTON---
int buttonPin = 12;

// ---MELODY---
// notes in the melody:
int melody[] = {
  NOTE_D4, NOTE_D4, NOTE_D5, NOTE_A4, NOTE_GS4, NOTE_G4, NOTE_F4, NOTE_D4, NOTE_F4, NOTE_G4, NOTE_C4, NOTE_C4
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  8, 8, 4, 2, 4, 4, 4, 8, 8, 8, 8, 8
};


// run once, when the sketch starts
void setup()  {

  // ---LED---
  // initialize digital pins from leds as an output.
  pinMode(ledPin, OUTPUT);
  pinMode(ledPinGreen, OUTPUT);
  pinMode(ledPinYellow, OUTPUT);
  pinMode(ledPinRed, OUTPUT);
  pinMode(ledPinWhite, OUTPUT);

  // ---BUTTON---
  // initialize digital pin from button as an input.
  pinMode(buttonPin, INPUT);
}   // end of the setup method

// run over and over again
void loop() {
  // ---LED---
  // the white led on pin 6 blinks constantly
  digitalWrite(ledPin, HIGH);
  delay(1000);
  digitalWrite(ledPin, LOW);
  delay(500);

  // ---BUTTON---
  //read the input pin
  int buttonState = digitalRead(buttonPin);

  //if button is pressed, play the melody
  if (buttonState == 1) {
    // ---MELODY---
    music();
  }

  // ---LED---
  //turn off all the leds
  digitalWrite(ledPinWhite, LOW);
  digitalWrite(ledPinRed, LOW);
  digitalWrite(ledPinGreen, LOW);
  digitalWrite(ledPinYellow, LOW);
}   // end of the loop method


// creating the melody
void music() {
  //turn the white blinking led off
  digitalWrite(ledPin, LOW);

  // ---leds interacting with the notes uf the melody---
  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < 12; thisNote++) {

    // calculates the note duration ==> take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(8, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(8);

    // ---LED---
    switch (thisNote) {
      // turn the green led on
      case 0:
        digitalWrite(ledPinWhite, LOW);
        digitalWrite(ledPinRed, LOW);
        digitalWrite(ledPinYellow, LOW);
        digitalWrite(ledPinGreen, HIGH);
        break;

      case 1:
        digitalWrite(ledPinWhite, LOW);
        digitalWrite(ledPinRed, LOW);
        digitalWrite(ledPinYellow, LOW);
        digitalWrite(ledPinGreen, HIGH);
        break;

      case 2:
        digitalWrite(ledPinWhite, LOW);
        digitalWrite(ledPinRed, LOW);
        digitalWrite(ledPinYellow, LOW);
        digitalWrite(ledPinGreen, HIGH);
        break;

      // turn the white led on
      case 3:
        digitalWrite(ledPinRed, LOW);
        digitalWrite(ledPinGreen, LOW);
        digitalWrite(ledPinYellow, LOW);
        digitalWrite(ledPinWhite, HIGH);
        break;

      // turn the yellow led on
      case 4:
        digitalWrite(ledPinWhite, LOW);
        digitalWrite(ledPinRed, LOW);
        digitalWrite(ledPinGreen, LOW);
        digitalWrite(ledPinYellow, HIGH);
        break;

      case 5:
        digitalWrite(ledPinWhite, LOW);
        digitalWrite(ledPinRed, LOW);
        digitalWrite(ledPinGreen, LOW);
        digitalWrite(ledPinYellow, HIGH);
        break;

      // turn the red led on
      case 6:
        digitalWrite(ledPinWhite, LOW);
        digitalWrite(ledPinGreen, LOW);
        digitalWrite(ledPinYellow, LOW);
        digitalWrite(ledPinRed, HIGH);
        break;

      // turn the green led on
      case 7:
        digitalWrite(ledPinWhite, LOW);
        digitalWrite(ledPinRed, LOW);
        digitalWrite(ledPinYellow, LOW);
        digitalWrite(ledPinGreen, HIGH);
        break;

      // turn the red led on
      case 8:
        digitalWrite(ledPinWhite, LOW);
        digitalWrite(ledPinGreen, LOW);
        digitalWrite(ledPinYellow, LOW);
        digitalWrite(ledPinRed, HIGH);
        break;

      // turn the yellow led on
      case 9:
        digitalWrite(ledPinRed, LOW);
        digitalWrite(ledPinGreen, LOW);
        digitalWrite(ledPinWhite, LOW);
        digitalWrite(ledPinYellow, HIGH);
        break;

      // turn the yellow led on
      case 10:
        digitalWrite(ledPinRed, LOW);
        digitalWrite(ledPinGreen, LOW);
        digitalWrite(ledPinYellow, LOW);
        digitalWrite(ledPinWhite, HIGH);
        break;

      case 11:
        digitalWrite(ledPinRed, LOW);
        digitalWrite(ledPinGreen, LOW);
        digitalWrite(ledPinYellow, LOW);
        digitalWrite(ledPinWhite, HIGH);
        break;
    }  // end of the switch case
  }  // end of the for-loop
}   // end of the music method

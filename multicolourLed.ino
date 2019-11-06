/* Button and LED

   While the button is pressed, the led will lighten up in different colors.
   
   Little tip: Hold the button for a longer time pressed to see the full lightshow.

   The constelation:
   - button attached to pin 7 from 5.0V
   - attached to pin 7 from ground
   - led attached to pin 6 from ground
   - 10K resistor attached to pin 6 from ground

   @author Mia Gudelj, Clarissa Sulivan
   @since 23.10.2019
   @version 1.0
*/

// fixed variables --> won't change
const int ledPin = 6;   // number of LED pin
const int buttonPin = 7;  // number of button pin

// valuable variables --> will change
int buttonState = 0;    // variable for reading the pushbutton status

void setup() {
  pinMode(ledPin, OUTPUT);    // initialize the LED pin as an output:
  pinMode(buttonPin, INPUT);    // initialize the button pin as an input:
}

void loop() {
  buttonState = digitalRead(buttonPin);   // read the state of the pushbutton value:

  // check if the pushbutton is pressed.
  // if it is pressed ==> buttonState is HIGH:
  if (buttonState == HIGH) {
    digitalWrite(ledPin, HIGH);
  } else {
    // turn LED off:
    digitalWrite(ledPin, LOW);
  }
}

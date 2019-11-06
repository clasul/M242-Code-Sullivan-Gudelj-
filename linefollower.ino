#include <Wire.h>
#include <Zumo32U4.h>

// maximum turn speed
const uint16_t maxSpeed = 400;

Zumo32U4Buzzer buzzer;
Zumo32U4LineSensors lineSensors;
Zumo32U4Motors motors;
Zumo32U4ButtonA buttonA;
Zumo32U4LCD lcd;

int16_t lastError = 0;

#define NUM_SENSORS 5
unsigned int lineSensorValues[NUM_SENSORS];
void loadCustomCharacters()
{
  static const char levels[] PROGMEM = {
    0, 0, 0, 0, 0, 0, 0, 63, 63, 63, 63, 63, 63, 63
  };
  lcd.loadCustomCharacter(levels + 0, 0);  // 1 bar
  lcd.loadCustomCharacter(levels + 1, 1);  // 2 bars
  lcd.loadCustomCharacter(levels + 2, 2);  // 3 bars
  lcd.loadCustomCharacter(levels + 3, 3);  // 4 bars
  lcd.loadCustomCharacter(levels + 4, 4);  // 5 bars
  lcd.loadCustomCharacter(levels + 5, 5);  // 6 bars
  lcd.loadCustomCharacter(levels + 6, 6);  // 7 bars
}

void printBar(uint8_t height)
{
  if (height > 8) {
    height = 8;
  }
  const char barChars[] = {' ', 0, 1, 2, 3, 4, 5, 6, 255};
  lcd.print(barChars[height]);
}


// calibrates the sensores to read the line
void calibrateSensors()
{
  // clears text on lcd display
  lcd.clear();

  // wait 1 second and begin calibrating
  delay(1000);
  for (uint16_t i = 0; i < 120; i++)
  {
    if (i > 30 && i <= 90)
    {
      motors.setSpeeds(-200, 200);
    }
    else
    {
      motors.setSpeeds(200, -200);
    }

    lineSensors.calibrate();
  }
  motors.setSpeeds(0, 0);
}

// displays graph of readings on display when user presses A
void showReadings()
{
  lcd.clear();

  while (!buttonA.getSingleDebouncedPress())
  {
    lineSensors.readCalibrated(lineSensorValues);

    lcd.gotoXY(0, 0);
    for (uint8_t i = 0; i < NUM_SENSORS; i++)
    {
      uint8_t barHeight = map(lineSensorValues[i], 0, 1000, 0, 8);
      printBar(barHeight);
    }
  }
}

void setup()
{


  lineSensors.initThreeSensors();

  loadCustomCharacters();
  lcd.clear();
  lcd.print(F("Press A"));
  lcd.gotoXY(0, 1);
  lcd.print(F("calibrate"));
  buttonA.waitForButton();

  calibrateSensors();

  showReadings();

  // plays music and starts driving once finished
  lcd.clear();
  lcd.print(F("Go!"));
  buzzer.play("L16 cdegreg4");
  while (buzzer.isPlaying());
}

void loop()
{
  // gets the position of the line
  int16_t position = lineSensors.readLine(lineSensorValues);
  int16_t error = position - 2000;
  int16_t speedDifference = error / 4 + 6 * (error - lastError);

  lastError = error;

  // gets motor speeds individually
  int16_t leftSpeed = (int16_t)maxSpeed + speedDifference;
  int16_t rightSpeed = (int16_t)maxSpeed - speedDifference;

  // constrains the motor speeds
  leftSpeed = constrain(leftSpeed, 0, (int16_t)maxSpeed);
  rightSpeed = constrain(rightSpeed, 0, (int16_t)maxSpeed);

  motors.setSpeeds(leftSpeed, rightSpeed);
}

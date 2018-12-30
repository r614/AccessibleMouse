
/*
  JoystickMouseControl
  Controls the mouse from a joystick on an Arduino Leonardo, Micro or Due.
  Uses a pushbutton to turn on and off mouse control, and a second pushbutton
  to click the left mouse button.
  Hardware:
  - 2-axis joystick connected to pins A0 and A1
  - pushbuttons connected to pin D2 and D3
  The mouse movement is always relative. This sketch reads two analog inputs
  that range from 0 to 1023 (or less on either end) and translates them into
  ranges of -6 to 6.
  The sketch assumes that the joystick resting values are around the middle of
  the range, but that they vary within a threshold.
  WARNING: When you use the Mouse.move() command, the Arduino takes over your
  mouse! Make sure you have control before you use the command. This sketch
  includes a pushbutton to toggle the mouse control state, so you can turn on
  and off mouse control.
  created 15 Sep 2011
  updated 28 Mar 2012
  by Tom Igoe
  This example code is in the public domain.
  http://www.arduino.cc/en/Tutorial/JoystickMouseControl
*/
#include <Mouse.h>        
#include <mpx5700.h>
#include <Keyboard.h>

//Call the first instance of the class so you have the ability to call built in functions of library
mpx5700 mpx;


// Here we would have the data pin 1 connected to A0, we then set that to the analog zero on the arduino board.

int sensorPin = A0;    // Select input pin for the pressure sensor
int sensorValue = 0;   // Variable stores value coming from the sensor
boolean didClick = false;
boolean scrollMode = false;

// set pin numbers for switch, joystick axes, and LED:
const int switchPin = 2;      // switch to turn on and off mouse control
const int mouseButton = 3;    // input pin for the mouse pushButton
const int xAxis = A1;         // joystick X axis
const int yAxis = A2;         // joystick Y axis
const int ledPin = 5;         // Mouse control LED


// parameters for reading the joystick:
int range = 12;               // output range of X or Y movement
int responseDelay = 5;        // response delay of the mouse, in ms
int threshold = range / 4;    // resting threshold
int center = range / 2;       // resting position value

bool mouseIsActive = false;    // whether or not to control the mouse
int lastSwitchState = LOW;        // previous switch state

void setup() {
  pinMode(switchPin, INPUT);       // the switch pin
  pinMode(ledPin, OUTPUT);         // the LED pin
  // take control of the mouse:
  Mouse.begin();
  
}

void loop() {

  int voltageReading = analogRead(sensorPin);
  if (voltageReading > 40 || voltageReading < 20) {
   
  } else {
  
    if (voltageReading < 33 && voltageReading > 29){
      didClick = false; 
  }
    if (voltageReading > 33 && didClick == false) {
      Mouse.click(MOUSE_LEFT);
      didClick = true;
      delay(40);
    }
    if (voltageReading < 30 && didClick == false) {
      while (analogRead(sensorPin) < 30);
      delay(500);

      if (analogRead(sensorPin) < 30) {

        Keyboard.press(KEY_LEFT_ALT);
        Keyboard.write('s');
        delay(100);
        Keyboard.releaseAll();
        didClick = true;
      }
      else if (analogRead(sensorPin) > 33) {
        scrollMode = !scrollMode;
        didClick = true;      
      } else {

        Mouse.click(MOUSE_RIGHT);
        didClick = true;
      }
      
      delay(40);
    }

    
  }
  
   

  int xReading = readAxis(A1);
  int yReading = readAxis(A2) * -1;

  // if the mouse control state is active, move the mouse:

  Serial.println(yReading);
  if (scrollMode == false) {
    Mouse.move(xReading, yReading, 0);
  }
  else {
    while (yReading > 0) {
      Keyboard.press(KEY_DOWN_ARROW);
      yReading = readAxis(A2) * -1;
    }
    while (yReading < 0) {
      Keyboard.press(KEY_UP_ARROW);
      yReading = readAxis(A2) * -1;
    }
    Keyboard.releaseAll();
  }
   
  

  delay(responseDelay);
}

/*
  reads an axis (0 or 1 for x or y) and scales the analog input range to a range
  from 0 to <range>
*/

int readAxis(int thisAxis) {
  // read the analog input:
  int reading = analogRead(thisAxis);

  // map the reading from the analog input range to the output range:
  reading = map(reading, 0, 1023, 0, range);

  // if the output reading is outside from the rest position threshold, use it:
  int distance = reading - center;

  if (abs(distance) < threshold) {
    distance = 0;
  }

  // return the distance for this axis:
  return distance;
}

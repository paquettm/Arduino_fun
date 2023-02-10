// Define Pins
#define RED 6
#define GREEN 5
#define  BLUE 3
#define PHOTOCELL A0
#define LED 9

#include "Registry.h"
#include "LedOutput.h"
#include "PIDLedOutput.h"

// define variables
Registry registry;
#define delayTime 1 // fading time between colors


//define and register red, green, blue LEDs with different PWM rates of change
void setup(){
  Serial.begin(9600); // initialize serial communication at 9600 baud rate

  LedOutput redLed(RED,0,1); 
  LedOutput greenLed(GREEN,0,1); 
  LedOutput blueLed(BLUE,0,1); 
  
  PIDLedOutput controlledLed(PHOTOCELL, LED, 110);

  registry.add(&redLed);
  registry.add(&greenLed);
  registry.add(&blueLed);
  registry.add(&controlledLed);
}

unsigned long previousTime = 0;
const int interval = 15; // perform task every 10 milliseconds
unsigned long currentTime = interval;

// main loop to call the registry update each cycle
void loop()
{
  currentTime = millis();
  if (currentTime - previousTime >= interval) {
    previousTime = currentTime;
    registry.message("ledOutput/update");
  }
  delay(delayTime);
}


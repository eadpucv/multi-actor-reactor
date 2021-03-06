/**

    Actor Reactor - CLAC
    Taller de Espacios Expositivos e[ad]
    Octubre 2017

*/
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <OnewireKeypad.h>
#include <AccelStepper.h>

Adafruit_PCD8544 display = Adafruit_PCD8544(7, 5, 6, 4, 3);
AccelStepper stepper(AccelStepper::DRIVER, 9, 8); // CLK+(paso) -> pin 9 --- CW+(direccion) -> pin 8

int stepToGo;
float bounce;
int halfMaxSteps = 4000;

void setup () {

  Serial.begin(57600);
  pinMode(12, INPUT);
  Serial.setTimeout(10000);
  digitalWrite(4, 0);
  pinMode(13, OUTPUT);
  delay(10);
  pinMode(13, INPUT);

  stepper.setMaxSpeed(1500.0);
  stepper.setSpeed(120.0);
  stepper.setAcceleration(2000.0);

  display.begin();
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(0, 0);
  display.println("vamos!");
  display.display();
  display.clearDisplay();
  display.display();
}



void loop() {

  bounce = sin(float(millis()) / 300.0) * halfMaxSteps;
  stepToGo = halfMaxSteps + round(bounce);
  
  stepper.moveTo(stepToGo);
  stepper.run();
  
  //stepper.runToNewPosition(stepToGo);
  Serial.println(stepToGo);

  display.clearDisplay();
  display.display();
  display.println("solo motor");
  display.display();
}


/**

    Actor Reactor - CLAC
    Taller de Espacios Expositivos e[ad]
    Octubre 2017

    Test on Screen
*/

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <OnewireKeypad.h>
#include <AccelStepper.h>
#include <EEPROM.h>
#include <SoftwareSerial.h>
#include <OSCMessage.h>

#define DIR_SENSOR_MIN 0
#define DIR_SENSOR_MAX 5
#define DIR_ACTUATOR_MIN 10
#define DIR_ACTUATOR_MAX 15

#define DIR_BEZIER_A 20
#define DIR_BEZIER_B 25
#define DIR_BEZIER_C 30
#define DIR_BEZIER_D 35

#define ID 1
// #define WLAN_ADDR  "224.0.0.1"         // receiving Router ip
#define WLAN_ADDR  "192.168.0.1"          // receiving Router ip
#define PORT  1112
#define WLAN_SSID  "AC"                   // wifi SSID
#define WLAN_PASS  "actor-reactor"        // wifi password 


float min_sensor = 0, min_actuator = 0, max_sensor = 0, max_actuator = 0;
float bezier_A = 0, bezier_B = 0, bezier_C = 0, bezier_D = 0, motor_pos = 0, last_motor_pos;
float EPSILON = 9.999999747378752E-5f;
boolean variable;
boolean wifi = false;

//EEPROM.get(DIR_SENSOR_MIN, min_sensor);
//EEPROM.get(DIR_SENSOR_MAX, max_sensor);
//EEPROM.get(DIR_ACTUATOR_MAX, max_actuator);

char insert[10];
int i = 0;
double normalize;
boolean mainmenu_disp = 0, resp;
boolean back = 0;
boolean endstop, endstop_activation = 0, endstop_position = 0;
boolean show_adjust = 0;
float sonar_read, acum_sonar_read;
int analog_counter = 0;
word previous_millis, actual_millis, diferencia;

float A = 0.02;
float B = 0.98;
float softenMotorPos = 0;

// Software SPI (slower updates, more flexible pin options):
// pin 7 - Serial clock out (SCLK)
// pin 6 - Serial data out (DIN)
// pin 5 - Data/Command select (D/C)
// pin 4 - LCD chip select (CS)
// pin 3 - LCD reset (RST)

Adafruit_PCD8544 display = Adafruit_PCD8544(7, 5, 6, 4, 3);
//AccelStepper stepper(AccelStepper::DRIVER, 9, 8); // CLK+(paso) -> pin 9 --- CW+(direccion) -> pin 8
AccelStepper stepper(2, 9, 8);

char KEYS[] = {
  '1', '2', '3', 'A',
  '4', '5', '6', 'B',
  '7', '8', '9', 'C',
  'Y', '0', 'N', 'D'
};

OnewireKeypad <Print, 16 > KP2(Serial, KEYS, 4, 4, A0, 4700, 1000, ExtremePrec );
SoftwareSerial wifiLink(11, 10);

void setup () {
  Serial.begin(57600);
  pinMode(12, INPUT);
  wifiLink.begin(57600);
  Serial.setTimeout(10000);
  digitalWrite(4, 0);
  pinMode(13, OUTPUT);
  delay(10);
  pinMode(13, INPUT);

  stepper.setMaxSpeed(600.0);
  stepper.setAcceleration(10000.0);
  stepper.setCurrentPosition(0);
  stepper.moveTo(motor_pos);

  resp = wifiLink.find("ready\r\n");
  wifiLink.println("AT+CWMODE=1");
  resp = wifiLink.find("OK\r\n");

  // connect to wifi

  wifiLink.println("AT+CIPMUX=1");
  resp = wifiLink.find("OK\r\n");
  wifiLink.print("AT+CIPSTART=4,\"UDP\",\"");
  wifiLink.print(WLAN_ADDR);
  wifiLink.print("\",54321,"); // osc port
  wifiLink.print(PORT);
  wifiLink.println(",0");
  resp = wifiLink.find("OK\r\n");
  wifiLink.setTimeout(1000);

  // display wifi status

  display.begin();
  display.clearDisplay();
  display.display();
  display.setContrast(60);
  display.setRotation(2);

  /*
    int attempts = 20;
    int count = 0;

    do {
    wifiLink.print("AT+CWJAP=\"");
    wifiLink.print(WLAN_SSID);
    wifiLink.print("\",\"");
    wifiLink.print(WLAN_PASS);
    wifiLink.println("\"");
    resp = wifiLink.find("OK\r\n");

    if (resp) {
      wifi = true;
      Serial.println(resp);
      Serial.println("conectado!");
      display.clearDisplay();
      display.display();
      display.println("wifi OK!!!");
      display.display();
      delay(1500);
      break;
      count = attempts;
    }
    display.clearDisplay();
    display.display();
    display.println("wifi attempt");
    display.print(count);
    display.print("/");
    display.print(attempts);
    display.display();
    count ++;
    } while (count < attempts);
  */
  previous_millis = 0;
  actual_millis = millis();
  KP2.SetKeypadVoltage(4.7);

  EEPROM.get(DIR_SENSOR_MIN, min_sensor);
  EEPROM.get(DIR_SENSOR_MAX, max_sensor);
  EEPROM.get(DIR_ACTUATOR_MIN, min_actuator);
  EEPROM.get(DIR_ACTUATOR_MAX, max_actuator);

  EEPROM.get(DIR_BEZIER_A, bezier_A);
  EEPROM.get(DIR_BEZIER_B, bezier_B);
  EEPROM.get(DIR_BEZIER_C, bezier_C);
  EEPROM.get(DIR_BEZIER_D, bezier_D);

  // write_eeprom(); // write default values if keypad not working

  Serial.println("done setup");
}

// position = 0 -> endstop al inicio
// position = 1 -> endstop al final

void endstop_action() {
  stepper.setCurrentPosition(0);
  if (last_motor_pos < motor_pos) {
    do {
      motor_pos--;
      stepper.moveTo(motor_pos);
      stepper.run();
    } while (digitalRead(12) == 0);
    stepper.runToNewPosition(-10);
    stepper.setCurrentPosition(0);
  }
  else if (last_motor_pos > motor_pos) {
    do {
      motor_pos++;
      stepper.moveTo(motor_pos);
      stepper.run();
    } while (digitalRead(12) == 0);
  }
  stepper.setCurrentPosition(0);
  motor_pos = 0;
}

void loop() {
  sonar_read = analogRead(A2) * 1.26;

  display.clearDisplay();
  display.display();
  display.println("Prueba de\nsensor");
  display.println("\n");
  display.print("sonar ");
  display.println(sonar_read);
  display.display();
  Serial.println(sonar_read);
  delay(10);
}


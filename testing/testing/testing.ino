// Importing AllLibrary
#include <OneWire.h>
#include <DallasTemperature.h> 
#include <Servo.h> 
#include <SPI.h>
#include <Wire.h>

// Create objects 
Servo myservo;

#define ONE_WIRE_BUS 2
OneWire oneWire(ONE_WIRE_BUS);

// Pass oneWire reference to DallasTemperature library
DallasTemperature sensors(&oneWire);

// Define Pin
int rHeater = 7;
int rPump = 8;
int servoPin = A0; 

void setup() {
  sensors.begin();
  Serial.begin(9600);
  myservo.attach(A0);
  
  pinMode(rHeater, OUTPUT);
  pinMode(rPump, OUTPUT);

  digitalWrite(rHeater, HIGH);
  digitalWrite(rPump, HIGH);
}

void loop() {
  // Testing Components Loop!
  heaterOn();
  delay(5000);  
  pumpOn();
  delay(5000);
  heaterOff();
  pumpOff();
  servoRound();
  tampilSuhu();
  delay(1000);
}

// Fungsi - Fungsi !delay(1000);
void heaterOn(){
  digitalWrite(rHeater,LOW);
}

void heaterOff(){
  digitalWrite(rHeater, HIGH);
}

void pumpOn(){
  digitalWrite(rPump,LOW);
}

void pumpOff(){
  digitalWrite(rPump, HIGH);
}

void servoRound(){
 int pos = 0;
 for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(25);                       // waits 15ms for the servo to reach the position
  }
  
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(25);                       // waits 15ms for the servo to reach the position
  }
}

void tampilSuhu(){
  // Send the command to get temperatures
  sensors.requestTemperatures(); 

  //print the temperature in Celsius
  Serial.print("Temp: ");
  Serial.print(sensors.getTempCByIndex(0));
  
  delay(500);
}

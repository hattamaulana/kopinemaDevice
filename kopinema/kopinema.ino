// Importing AllLibrary
#include <OneWire.h>
#include <DallasTemperature.h> 
#include <Servo.h> 
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Define Pin
#define ONE_WIRE_BUS 2
int rHeater = 7;
int rPump = 8;
int servoPin = A0; 

// Define Screen
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16
static const unsigned char PROGMEM logo_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000 };
// Create objects 
Servo myservo; 
OneWire oneWire(ONE_WIRE_BUS);  

// Pass oneWire reference to DallasTemperature library
DallasTemperature sensors(&oneWire);

void setup() {
  Serial.begin(9600);

  sensors.begin();  // Start up the library

  pinMode(rHeater, OUTPUT);
  pinMode(rPump, OUTPUT);
  myservo.attach(servoPin);

  digitalWrite(rHeater, HIGH); // Offline #1 Channel at Setup
  digitalWrite(rPump, HIGH); // Offline #2 Channel at Setup

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(2000); // Pause for 2 seconds

  // Clear the buffer
  display.clearDisplay(); 
  int totalmilis;
  int rehatDulu = 54400;
}

void loop() {
  sensors.requestTemperatures();
  if((int) sensors.getTempCByIndex(0) > 90){
    screenHeatSensor();
    pumpOn();
    muterTest();
    heaterOff();
    delay(500);  
    totalmilis += 500;
    if (totalmilis == rehatDulu){
      muterTest();
      pumpOff();
      delay(30000);
      rehatDulu += rehatDulu;        
    }
  } else {
    heaterOn();
    pumpOff();
    screenHeatSensor();
    delay(1000);
    totalmilis += 1000;
  }
}

// Fungsi - Fungsi !
void screenHeatSensor(){
  sensors.requestTemperatures(); 
  display.clearDisplay();

  display.setTextSize(3);             // Normal 1:1 pixel scale
  display.setTextColor(WHITE);        // Draw white text
  display.setCursor(0,0);             // Start at top-left corner
  display.print(sensors.getTempCByIndex(0));
  display.print(F(" C"));

  display.display();
  delay(2000);
}

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

void muterTest(){
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

// Importing Library
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <OneWire.h>
#include <DallasTemperature.h>
// Include the Servo library 
#include <Servo.h> 

// Pin Out Places
#define ONE_WIRE_BUS 2
int rHeater = 7;
int rPump = 8;
// Declare the Servo pin 
int servoPin = A0; 
// Create a servo object 
Servo Servo1; 

// Define Screen
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels


// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define NUMFLAKES     10 // Number of snowflakes in the animation example

// Setup a oneWire instance to communicate with any OneWire device
OneWire oneWire(ONE_WIRE_BUS);  

// Pass oneWire reference to DallasTemperature library
DallasTemperature sensors(&oneWire);

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

void setup() {
  Serial.begin(9600);

  sensors.begin();  // Start up the library

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

  // Draw a single pixel in white
  display.drawPixel(10, 10, WHITE);

  // Show the display buffer on the screen. You MUST call display() after
  // drawing commands to make them visible on screen!
  display.display();
  delay(2000);
  // display.display() is NOT necessary after every single drawing command,
  // unless that's what you want...rather, you can batch up a bunch of
  // drawing operations and then update the screen all at once by calling
  // display.display(). These examples demonstrate both approaches...
  pinMode(rHeater, OUTPUT);
  pinMode(rPump, OUTPUT);

  digitalWrite(rHeater, HIGH); // Offline #1 Channel at Setup
  digitalWrite(rPump, HIGH); // Offline #2 Channel at Setup

  //testanimate(logo_bmp, LOGO_WIDTH, LOGO_HEIGHT); // Animate bitmaps
}

void loop() {
  screenHeatSensor();
  Serial.println("DS18B20 Check");
  delay(10000);
  heaterTest();
  Serial.println("Heater Check");
  delay(5000);
  pumpTest();
  Serial.println("Pump Check");
  delay(5000);
  muterTest();
  Serial.println("Servo Check");
}

void screenHeatSensor(){
  /* Send the command to get temperatures
  sensors.requestTemperatures(); 
  display.clearDisplay();

  display.setTextSize(4);             // Normal 1:1 pixel scale
  display.setTextColor(WHITE);        // Draw white text
  display.setCursor(0,0);             // Start at top-left corner
  display.print((int)sensors.getTempCByIndex(0));
  display.println(F(" C"));

  display.display();
  delay(1000);
  */
  sensors.requestTemperatures(); 
  Serial.println(sensors.getTempCByIndex(0));
}

void heaterTest(){
  digitalWrite(rHeater,LOW);
  delay(2000);
  digitalWrite(rHeater, HIGH);
}

void pumpTest(){
  digitalWrite(rPump,LOW);
  delay(2000);
  digitalWrite(rPump, HIGH);
}

void muterTest(){
  // Make servo go to 0 degrees 
   Servo1.write(0); 
   delay(1000); 
   // Make servo go to 90 degrees 
   Servo1.write(90);  
   delay(1000);
   // Make servo go to 180 degrees 
   Servo1.write(180); 
   delay(1000);
   Servo1.write(90);
   delay(1000);
}

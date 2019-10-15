#include <OneWire.h>
#include <DallasTemperature.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Data wire is plugged into digital pin 2 on the Arduino
#define ONE_WIRE_BUS 2


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


// Setup a oneWire instance to communicate with any OneWire device
OneWire oneWire(ONE_WIRE_BUS);	

// Pass oneWire reference to DallasTemperature library
DallasTemperature sensors(&oneWire);

void setup(void)
{
  sensors.begin();	// Start up the library
  Serial.begin(9600);

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
}

void loop(void)
{ 
//  // Send the command to get temperatures
//  sensors.requestTemperatures(); 
//
//  //print the temperature in Celsius
//  Serial.print("Temperature: ");
//  Serial.print(sensors.getTempCByIndex(0));
//  Serial.print((char)176);//shows degrees character
//  Serial.print("C  |  ");
//  
//  //print the temperature in Fahrenheit
//  Serial.print((sensors.getTempCByIndex(0) * 9.0) / 5.0 + 32.0);
//  Serial.print((char)176);//shows degrees character
//  Serial.println("F");
//  
//  delay(500);
  screenHeatSensor();
}

void screenHeatSensor(){
  sensors.requestTemperatures(); 
  Serial.println(sensors.getTempCByIndex(0));
  display.clearDisplay();

  display.setTextSize(3);             // Normal 1:1 pixel scale
  display.setTextColor(WHITE);        // Draw white text
  display.setCursor(0,0);             // Start at top-left corner
  display.print(sensors.getTempCByIndex(0));
  display.print(F(" C"));

  display.display();
}

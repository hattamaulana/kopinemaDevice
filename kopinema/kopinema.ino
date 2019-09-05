// Including Library
#include <OneWire.h>
#include <DallasTemperature.h>

// Setting Pin 
int rHeater = A0;
int rPump = A1;
#define ONE_WIRE_BUS 2 // Data wire is plugged into digital pin 2 on the Arduino
OneWire oneWire(ONE_WIRE_BUS); // Setup a oneWire instance to communicate with any OneWire device
DallasTemperature sensors(&oneWire);// Pass oneWire reference to DallasTemperature library

// Variable
int delayValue = 1000;
byte indikator = 13;
byte sensorInt = 0;
byte flowsensor = 2;

float KONSTANTA = 4.5;

volatile byte pulseCount;

float debit;
unsigned int flowmlt;
unsigned long totalmlt;
unsigned long oldtime;

void setup() {
    // WaterFlow
    pinMode(indikator, OUTPUT);
    digitalWrite(indikator, HIGH);

    pinMode(flowsensor, INPUT);
    digitalWrite(flowsensor, HIGH);

    // FlowSensor Variable
    pulseCount = 0; debit = 0.0; flowmlt = 0;
    totalmlt = 0; oldtime = 0;

    attachInterrupt(sensorInt, pulseCount, FALLING);

    // Relay
    pinMode(rHeater, OUTPUT);
    pinMode(rPump, OUTPUT);
    
    digitalWrite(rHeater, HIGH);
    digitalWrite(rPump, HIGH);
    
    // DS18B20
    sensors.begin();	// Start up the library
    
    // Starting listening
    Serial.begin(9600);
}

void loop() {
    digitalWrite(rHeater, LOW);
    
    if (sensors.getTempCByIndex(0) > 90){
        digitalWrite(rHeater, HIGH);
        digitalWrite(rPump, LOW);
        if ((milis() - oldtime) > 1000){
            detachInterrupt(sensorInt);
            debit = ((1000.0 / (millis() - oldTime)) * pulseCount) / konstanta;
            oldTime = millis();
            flowmlt = (debit / 60) * 1000;
            totalmlt += flowmlt;        
            
            unsigned int frac;
            
            Serial.print("Debit air: ");
            Serial.print(int(debit));
            Serial.print("L/min");
            Serial.print("\t");
            Serial.print("Volume: "); 
            Serial.print(totalmlt);
            Serial.println("mL"); 
            
            pulseCount = 0;
            attachInterrupt(sensorInt, pulseCounter, FALLING);
            if (totalmlt == target){
                digitalWrite(rPump, HIGH);
            }
        }
    }
}

void sPanas(){
    // Send the command to get temperatures
    sensors.requestTemperatures(); 
    
    //print the temperature in Celsius
    Serial.print("Temperature: ");
    Serial.print(sensors.getTempCByIndex(0));
    Serial.print((char)176);//shows degrees character
    Serial.print("C  |  ");
}

void pulseCounter(){
    // Increment the pulse counter
    pulseCount++;
}
